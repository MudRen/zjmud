// doctor.c

inherit NPC;
inherit F_DEALER;

void create()
{
	set_name("ʱ�Ź�", ({ "shi jiugong", "shi", "jiugong"}));
	set("str", 60);
	set("gender", "����");
	set("title", "ҩ���ƹ�");
	set("age", 66);
	set("long", "��˵ʱ�Ź�ԭ�ǽ����е���ҽ��\n");
	set("combat_exp", 250);
	set("attitude", "friendly");
	set("vendor_goods", ({
		__DIR__"obj/jinchuang",
		__DIR__"obj/yangjing",
	}));
       set("icon","00973");
	setup();
	carry_object(__DIR__"obj/choupao")->wear();
}

void init()
{
	add_action("do_list", "list");
	add_action("do_buy", "buy");
}
