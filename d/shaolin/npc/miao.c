// miao.c ���˷�

#include <ansi.h>;

inherit NPC;

string ask_me();
string ask_book();
string ask_hujia_book();

void create()
{
	set_name("���˷�", ({ "miao renfeng", "miao" }));
	set("gender", "����");
	set("nickname", YEL "�����" NOR);
	set("age", 37);
	set("long", @LONG
������ȥ��ɫ͸�ƣ��ƺ�����һ�㵭���Ľ�ֽ����ĸߴ���࣬ȷ
��ȫȻ����ƪ�������˳��档
LONG );
	set("attitude", "peaceful");
	set("str", 32);
	set("int", 31);
	set("con", 33);
	set("dex", 31);
    
	set("qi", 4500);
	set("max_qi", 4500);
	set("jing", 2200);
	set("max_jing", 2200);
	set("neili", 4800);
	set("max_neili", 4800);
	set("jiali", 120);
	set("combat_exp", 2200000);

	set_skill("force", 220);
	set_skill("hunyuan-yiqi", 220);
	set_skill("sword", 230);
	set_skill("miaojia-jian", 230);
	set_skill("dodge", 210);
	set_skill("feiyan-zoubi", 210);
	set_skill("strike", 225);
	set_skill("tianchang-zhang", 225);
	set_skill("parry", 230);

	map_skill("force", "hunyuan-yiqi");
	map_skill("sword", "miaojia-jian");
	map_skill("dodge", "feiyan-zoubi");
	map_skill("parry", "miaojia-jian");
	map_skill("strike", "tianchang-zhang");

	prepare_skill("strike", "tianchang-zhang");

	set("inquiry", ([
		"��һ��": (: ask_me :),
		"��������޵���" : "�⻰˵˵���ѣ����ܵ��棿",
	]));

	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/cloth/cloth")->wear();
}

string ask_me()
{
	object ob, me;

	me = this_player();
	if (me->query("family/family_name") != "�������")
		return "��������һ�����ӣ���ϧ����ϧ��\n";

	return "���겻�����˼��˶����������������ź����������Ȼ��"
	       "���ҵĺ��ˣ��ɶ�����ҽ�������Ȥ��";
}

int recognize_apprentice(object ob, string skill)
{
	if (ob->query("family/family_name") != "�������")
	{
		command("say ��������ʲô��˼��Ҫ�ǱȻ��ͷ��������");
		return -1;
	}

	if (skill != "miaojia-jian" && skill != "sword")
	{
		command("say ��ֻ���㽣���������������Ȥ�Ͳ�Ҫ�˷�ʱ���ˡ�");
		return -1;
	}

	if (! ob->query_temp("can_learn/miao"))
	{
		command("say �ã����Ȼ����Ȥ���Ǿ�Ҫ����ϸ�ˣ�");
		ob->set_temp("can_learn/huyizhi", 1);
	}

	return 1;
}
