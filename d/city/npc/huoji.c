// huoji. ҩ�̻��

inherit NPC;
inherit F_DEALER;

void create()
{
	set_name("ҩ�̻��", ({ "yaopu huoji", "huoji" }));
	set("str", 20);
	set("gender", "����");
	set("age", 18);
	set("long", "����ƽ��ҽ������������æ�ġ�\n");
	set("combat_exp", 250);
	set("attitude", "friendly");
	set("vendor_goods", ({
		"/clone/misc/yanbo",    // �в�
		"/clone/misc/jinchuang",
		"/clone/misc/yangjing",
		"/clone/misc/dust",
		"/clone/misc/fashao",
		"/clone/misc/shanghan",
		"/clone/misc/xiaoshu",
		"/clone/misc/dongshang",
		"/clone/misc/zhike",
		"/d/shenlong/obj/xionghuang",
	}));
      set("icon","00973");
	setup();
	carry_object("/clone/misc/cloth")->wear();
}

void init()
{
	add_action("do_list", "list");
	add_action("do_buy", "buy");
}
