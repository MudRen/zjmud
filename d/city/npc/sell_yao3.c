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
		  HERB("xiefen"),	 // Ы��
		HERB("xijiao"),	 // Ϭ��
		HERB("xiongdan"),       // �ܵ�
		HERB("xionghuang"),     // �ۻ�
		HERB("xuejie"),	 // Ѫ��
		HERB("xuelian"),	// ѩ��
		HERB("yanwo"),	  // ����
		HERB("yjhua"),	  // ���
		HERB("yuanzhi"),	// Զ־
		HERB("zihua"),	  // �ϻ�
		HERB("zzfen"),	  // �����
		HERB("shedan"),	  // �ߵ�
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
