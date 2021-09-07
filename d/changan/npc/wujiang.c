// wujiang.c �佫

inherit NPC;

void create()
{
	set_name("�佫", ({ "wu jiang", "wu", "jiang" }));
	set("gender", "����");
	set("age", random(10) + 30);
	set("str", 25);
	set("long", "���������ݣ�ɱ�����ڣ���Ȼ����ֻ�Ǹ���"
		    "��С�٣�����Ҳ�����μӹ�������ս�ۡ�\n");
	set("combat_exp", 80000);
	set("attitude", "peaceful");
	set_skill("unarmed", 70);
	set_skill("force", 70);
	set_skill("sword", 70);
	set_skill("dodge", 70);
	set_skill("parry", 70);
	set("max_qi", 700);
	set("max_jing", 600);
	set("neili", 400); 
	set("max_neili", 400);
	set("jiali", 15);
	set("max_jingli", 100);
	set("jing", 100);
	set("jingli_factor", 5);

	setup();
	carry_object(__DIR__"obj/changjian")->wield();
	carry_object(__DIR__"obj/zhanjia")->wear();
}

void init()
{
	object ob;
	::init();
	if (interactive(ob = this_player()) && 
	    ob->query_condition("killer")) 
	{
		remove_call_out("kill_ob");
		call_out("kill_ob", 1, ob);
	}
}

int accept_fight(object me)
{
	message_vision("�佫��$N����һ�ɣ��ȵ���߾����������"
		       "���ұ��ԣ��ǲ��ǻ�Ĳ����ˣ�\n\n", me);
	return 0;
}
