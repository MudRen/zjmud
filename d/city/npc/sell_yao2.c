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
		HERB("ruxiang"),	// ����
		HERB("shadan"),	 // �赨
		HERB("shancha"),	// ɽ�軨
		HERB("shanjia"),	// ɽ��
		HERB("shengdi"),	// ����
		HERB("shenglg"),	// ������
		HERB("sumu"),	   // ��ľ
		HERB("taoxian"),	// ����
		HERB("tenghuang"),      // �ٻ�
		HERB("tianqi"),	 // ����
		HERB("tugou"),	  // ����
		HERB("wulingzhi"),      // ����֬
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
