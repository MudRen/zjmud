// Npc: /kungfu/class/shaolin/qing-le.c
// Date: YZC 96/01/19

inherit NPC;

string ask_me_1();
string ask_me_2();

static string *check_skill = ({
	"buddhism",
	"dodge",
	"shaolin-shenfa",
	"force",
	"parry",
});

void create()
{
	set_name("���ֱ���", ({
		"qingle biqiu",
		"qingle",
		"biqiu",
	}));
	set("long",
		"����һλ���ǿ����׳��ɮ�ˣ�����û���������ȫ���ƺ��̺�\n"
		"�������������һϮ�ײ��ڱ����ģ��ƺ������ա�\n"
	);


	set("gender", "����");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 30);
	set("shen_type", 1);
	set("str", 17);
	set("int", 24);
	set("con", 20);
	set("dex", 22);
	set("max_qi", 350);
	set("max_jing", 200);
	set("neili", 350);
	set("max_neili", 350);
	set("jiali", 30);
	set("combat_exp", 5000);
	set("score", 100);

	set_skill("force", 30);
	set_skill("shaolin-xinfa", 30);
	set_skill("dodge", 30);
	set_skill("shaolin-shenfa", 30);
	set_skill("claw", 30);
	set_skill("yingzhua-gong", 30);
	set_skill("parry", 30);
	set_skill("buddhism", 30);
	set_skill("literate", 30);

	map_skill("force", "shaolin-xinfa");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("claw", "yingzhua-gong");
	map_skill("parry", "yingzhua-gong");

	prepare_skill("claw", "yingzhua-gong");

	create_family("������", 40, "����");

	set("inquiry", ([
		"����"       : (: ask_me_1 :),
		"��ʮ������" : (: ask_me_1 :),
		"��Ħ��" :     (: ask_me_2 :)
	]));

	setup();

	carry_object("/d/shaolin/obj/qing-cloth")->wear();
}


string ask_me_1()
{
	mapping fam, skl; 
	object ob;
	string *sname;
	int i;
	
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "������")
		return RANK_D->query_respect(this_player()) + 
		"�뱾��������������֪�˻��Ӻ�̸��";

	if ( (int)this_player()->query("guilty") > 0 )
		return RANK_D->query_respect(this_player()) + 
		"���۷����䣬������������ܸ��������ͣ�";

	if ( (int)this_player()->query_int() < 30 )
		return RANK_D->query_respect(this_player()) + 
		"���ʲ��������ܽ���ؾ�¥��";

	skl = this_player()->query_skills();
	sname  = sort_array( keys(skl), (: strcmp :) );

	for(i=0; i<sizeof(check_skill); i++) {
		if (skl[check_skill[i]] < 100) 
			return RANK_D->query_respect(this_player()) + 
			       "���������������ʸ���ȡ���͡�";
	}

	if ( (int)this_player()->query_skill("buddhism",1) < 150 )
		return RANK_D->query_respect(this_player()) + 
		"��ѧϰ�ϳ��书����Ҫ�Ը���𷨻������ǵ��������������޼���";

	ob = new("/d/shaolin/obj/allow-letter");
	ob->move(this_player());
	message_vision("$N���һ�����͡�\n",this_player());

	return "�ðɣ�ƾ������ͣ�������ɽ���ؾ����¥��ϰ�ϳ��书��";

}

string ask_me_2()
{
	mapping fam; 
	object ob;
	object me;
	int i;
	
	me = this_player();
	if (!(fam = me->query("family")) ||
	    fam["family_name"] != "������")
		return RANK_D->query_respect(me) + 
		"�뱾��������������֪�˻��Ӻ�̸��";

	for(i=0; i< sizeof(check_skill); i++) {
		if (me->query_skill(check_skill[i], 1) < 30)
		return RANK_D->query_respect(me) +
		       "��" + to_chinese(check_skill[i]) +
		       "�Ĺ���������������ȡ��Ħ�";
	}

	ob = new("/d/shaolin/obj/damo-ling");
	ob->move(me);
	message_vision("$N���һ���Ħ�\n",this_player());

	return "�ðɣ�ƾ�����Ħ�������������ʦ����ս��";

}
