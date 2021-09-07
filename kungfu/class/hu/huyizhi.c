// huyizhi.c ����֮

#include <ansi.h>;

inherit NPC;

string ask_me();
string ask_book();
string ask_hujia_book();

void create()
{
	set_name("����֮", ({ "hu yizhi", "hu" }));
	set("gender", "����");
	set("nickname", HIG "������" NOR);
	set("age", 37);
	set("long", @LONG
���˺������꣬ͷ�Ϲ���һΧ�׽���������һ˫��Ь��ȫȻһ��
��ũģ����
LONG );
	set("attitude", "peaceful");
	set("str", 36);
	set("int", 28);
	set("con", 31);
	set("dex", 33);
    
	set("qi", 4000);
	set("max_qi", 4000);
	set("jing", 2000);
	set("max_jing", 2000);
	set("neili", 4200);
	set("max_neili", 4200);
	set("jiali", 100);
	set("combat_exp", 1700000);

	set_skill("force", 180);	    // �����ڹ�
	set_skill("lengyue-shengong", 180); // ������
	set_skill("blade", 180);	    // ��������
	set_skill("baisheng-daofa", 180);   // ��ʤ����
	set_skill("dodge", 180);	    // ��������
	set_skill("taxue-wuhen", 180);      // ̤ѩ�޺�
	set_skill("parry", 180);	    // �����м�

	map_skill("force", "lengyue-shengong");
	map_skill("blade", "baisheng-daofa");
	map_skill("dodge", "taxue-wuhen");
	map_skill("parry", "baisheng-daofa");

	set("inquiry", ([
		"��ʤ����": (: ask_me :),
		"������"  : "�������Ѿ����ˣ�������������",
		"��ԲԲ"  : "������Ҳû�ܺ���˵�ϼ��仰...",
		"��԰԰"  : "������Ҳû�ܺ���˵�ϼ��仰...",
	]));

	setup();
	carry_object("/clone/weapon/gangdao")->wield();
	carry_object("/clone/cloth/cloth")->wear();
}

string ask_me()
{
	object ob, me;

	me = this_player();
	if (me->query("family/family_name") != "�������")
		return "���������ó��ı��£���Ҫ��Ҫ����������\n";

	return "�ܺ�... �ܺ�... ��Ȼ�Ǻ��ҵ��ӣ���û����Ȥѧѧ�ҵİ�ʤ������";
}

int recognize_apprentice(object ob, string skill)
{
	if (ob->query("family/family_name") != "�������")
	{
		command("say ��͵ѧ���Ǻ��Ҿ������ٺ�...");
		return -1;
	}

	if (skill != "baisheng-daofa")
	{
		command("say ��ֻ�����ʤ������������������ʦ��ȥѧ�ɡ�");
		return -1;
	}

	if (! ob->query_temp("can_learn/huyizhi/baisheng-daofa"))
	{
		command("say �ã��㿴����ˣ�");
		ob->set_temp("can_learn/huyizhi/baisheng-daofa", 1);
	}

	return 1;
}
