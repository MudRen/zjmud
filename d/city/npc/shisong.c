// shisong.c ʷ��

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("ʷ��", ({ "shi song", "shi", "song" }));
	set("gender", "����");
	set("title", "������");
	set("age", 35);
	set("str", 25);
	set("dex", 20);
	set("long", "����һ����׳���ӣ�����ģ��������Χһ�����ޡ�\n");
	set("combat_exp", 45000);
	set("shen_type", -1);
	set("attitude", "peaceful");

	set_skill("unarmed", 50);
	set_skill("force", 50);
	set_skill("whip", 80);
	set_skill("dodge", 50);
	set_skill("parry", 50);

	set_skill("yunlong-bian", 70);

	set_temp("apply/attack", 30);
	set_temp("apply/defense", 30);
	set_temp("apply/armor", 15);
	set_temp("apply/damage", 20);

	map_skill("whip", "yunlong-bian");
	map_skill("parry", "yunlong-bian");

	set("neili", 200); 
	set("max_neili", 200);
	set("jiali", 5);
	set("chat_chance", 1);
	set("chat_msg", ({
		"ʷ��һ���������ޣ�˵�������º�����ʷ�ɣ������ٱ����"
		"������ػᷴ����\n",
		"ʷ�ɴ�У����ˣ����ˣ�ͨͨ�������£� \n",
		"ʷ��˵�������ٱ��������£��书���������ڱ�������һȭ"
		"����һͷ��ţ��˭�Һ����ٱ����֣�\n",
	}));

	setup();
	carry_object(__DIR__"obj/junfu")->wear();
	carry_object(__DIR__"obj/hlbian")->wield();
	add_money("silver", 3);
}

void init()
{
	object me, ob;

	::init();

	ob = this_player();
	me = this_object();
	
	if (interactive(ob) &&
	    ! environment(ob)->query("no_fight") &&
	    (ob->query("combat_exp") > 10000) &&
	    (ob->query("party/party_name") == "��ػ�"))
	{
		command("say �������ػᷴ�����������ɣ�����\n");
		me->set_leader(ob);
		remove_call_out("kill_ob");
		call_out("kill_ob", 1, ob); 
	}
}
