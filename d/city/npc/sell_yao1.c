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
		HERB("honghua"),	// �컨
		HERB("hugu"),	   // ����
		HERB("juhua"),	  // �ջ�
		HERB("lanhua"),	 // ����
		HERB("lingxian"),       // ����
		HERB("lingzhi"),	// ��֥
		HERB("lurong"),	 // ¹��
		HERB("mahuang"),	// ���
		HERB("moyao"),	  // ûҩ
		HERB("niuhuang"),       // ţ��
		HERB("niuxi"),	  // ţϥ
		HERB("qianjinzi"),      // ǧ����
		HERB("renshen"),	// �˲�
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
