// bing2.c

inherit NPC;

void create()
{
	set_name("�����ٱ�", ({ "guan bing", "bing" }));
	set("age", 22);
	set("gender", "����");
	set("long", "�����ٱ��Ǿ�������ѵ���ģ�û����ñ�ȥ���ǡ�\n");
	set("attitude", "peaceful");

	set("str", 25);
	set("dex", 20);
	set("combat_exp", 50000);
	set("shen_type", 1);

	set_skill("unarmed", 70);
	set_skill("dodge", 70);
	set_skill("parry", 70);
	set_skill("sword", 70);
	set_skill("force", 70);
	set_temp("apply/attack", 80);
	set_temp("apply/defense", 80);
	set_temp("apply/damage", 40);
	set_temp("apply/armor", 80);

	set("chat_chance_combat", 10);
	set("chat_msg_combat", ({
		"�����ٱ��ȵ����󵨵��񣬾���֮�У������췴���ɣ�\n",
	}));
	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object(__DIR__"obj/guanfu4")->wear();
}

void init()
{
	object ob;
	::init();
	if (interactive(ob = this_player()) && 
		(int)ob->query_condition("killer")) {
		remove_call_out("kill_ob");
		call_out("kill_ob", 1, ob);
	}
}

int accept_fight(object me)
{
	command("say ��ү����������ɱ�ţ��������㵹ù��\n");
	me->apply_condition("killer", 500);
	kill_ob(me);
	return 1;
}
