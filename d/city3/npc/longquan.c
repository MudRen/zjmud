// longquan.c

#include <ansi.h>

inherit NPC;
inherit F_DEALER;

void create()
{
	set_name("����", ({ "long quan", "long" }));
	set("title","��ţ��ݽ�ϰ");
	set("long", "����ү�������Ҳ���˺ö���ͷ�ˣ����ϵ���׳��\n");
	set("gender", "����");
	set("age", 60);
	 set("icon","00723");
	set_skill("dodge", 80);
	set_skill("force", 80);
	set_skill("parry", 80);
	set_skill("claw", 80);
	set_skill("blade", 80);
	set_temp("apply/attack", 80);
	set_temp("apply/defense", 80);
	set_temp("apply/damage", 20);

	set("combat_exp", 400000);
	set("shen_type", 1);

	set("vendor_goods", ({
		"/clone/book/expert-sword",
		"/clone/book/expert-blade",
		"/clone/book/expert-dagger",
		"/clone/book/expert-unarmed",
		"/clone/book/expert-dodge",
		"/clone/book/expert-parry",
		"/clone/book/expert-force",
		"/clone/book/expert-staff",
		"/clone/book/expert-whip",
       		"/clone/book/expert-club",
		"/clone/book/expert-throwing",
	}));

	setup();
}

void init()
{
	add_action("do_buy", "buy");
	add_action("do_list", "list");
}

int recognize_apprentice(object ob)
{
	if (! (int)ob->query_temp("marks/jinniu_paied") == 1) return 0;
	return 1;
}
