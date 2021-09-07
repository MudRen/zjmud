// zhang.c
#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;
inherit F_MASTER;
inherit F_GUARDER;

void create()
{
	set_name("�ŵ���", ({ "zhang danyue", "zhang"}));
	set("title", HIY"������"BLU"����ʹ"NOR);
	set("long", "����һ�����´󺺣�������ͦ����ò���ϡ�\n" );
	set("gender", "����");

	set("age", 44);
	set("str", 28);
	set("con", 26);
	set("int", 28);
	set("dex", 24);

	set("max_qi", 3200);
	set("qi", 3200);
	set("max_jing",1600);
	set("neili", 3800); 
	set("max_neili", 3800);
	set("jiali", 60);

	set("combat_exp", 570000);
	set("shen_type", -1);
	set("attitude", "peaceful");

	set_skill("force", 140);
	set_skill("huntian-qigong", 145);
	set_skill("dodge", 130);
	set_skill("feiyan-zoubi", 130);
	set_skill("unarmed", 130);
	set_skill("changquan", 130);
	set_skill("shedao-qigong", 140);
	set_skill("shenlong-xinfa", 140);
	set_skill("parry", 140);
	set_skill("staff", 140);
	set_skill("literate", 50);

	map_skill("force", "shenlong-xinfa");
	map_skill("dodge", "xiaoyaoyou");
	map_skill("unarmed", "xianglong-zhang");
	map_skill("parry", "xianglong-zhang");

	create_family("������", 0, "����");

	set("coagents", ({
		([ "startroom" : "/d/shenlong/dating",
		   "id"	: "hong antong" ]),
	}));

	set("inquiry", ([
		"������" : "һ�������벻���������̵�(join shenlongjiao).\n",
		"�鰲ͨ" : "����Ƣ������,Ҫ�������Ĳźá�\n",
		"����"   : "����Ƣ������,Ҫ�������Ĳźá�\n",
		"���"   : "һ�������벻���������̵�(join shenlongjiao).\n",
		"�ں�"   : "���겻�ϣ������ɸ����������룡������ʥ��\n",
	]));

	setup();
	carry_object("/clone/misc/cloth")->wear();
	add_money("silver", 10);
}

void init()
{
	object ob;

	::init();
	if (interactive(ob = this_player()) && !is_fighting())
	{
		remove_call_out("greeting");
		call_out("greeting", 2, ob);
	}
}

void greeting(object ob)
{
	object obj;
	if (objectp(ob) &&
	    interactive(ob) && objectp(obj = present("used gao", ob)))
	{
		set("combat_exp", 100000);
		set("qi", 1000);
		set("jing", 1000);
	}
}

void attempt_apprentice(object ob)
{
	command("say ���߿������ң�");
	return;
}

