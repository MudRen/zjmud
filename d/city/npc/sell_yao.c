// huoji. ҩ�̻��
#include <ansi.h>
#include <medical.h>
inherit NPC;
inherit F_DEALER;

void create()
{
	set_name("��ҩ�̻��", ({ "yaopu huoji", "huoji" }));
	set("str", 20);
	set("gender", "����");
	set("age", 18);
	set("long", "����ƽ��ҽ������������æ�ġ�\n");
	set("combat_exp", 250);
	set("attitude", "friendly");
	set("vendor_goods", ({
		 HERB("chaihu"),	 // ���
		HERB("chenpi"),	 // ��Ƥ
		HERB("chuanwu"),	// ����
		HERB("dahuang"),	// ���
		HERB("dangui"),	 // ����
		HERB("duhuo"),	  // ����
		HERB("fangfeng"),       // ����
		HERB("fuzi"),	   // ����
		HERB("gsliu"),	  // ��ʯ��
		HERB("guiwei"),	 // ��β
		HERB("hafen"),	  // ���
		HERB("heshouwu"),       // ������

	}));
	setup();
	carry_object("/clone/misc/cloth")->wear();
}

void init()
{
	add_action("do_list", "list");
	add_action("do_buy", "buy");
}
