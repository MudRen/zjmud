// huanong.c

#include <ansi.h>
#include <command.h>

inherit NPC;
inherit F_DEALER;

void create()
{
	set_name("��ũ", ({ "hua nong", "nong" }));
	set("nickname","��ʵ��"); 

	set("gender", "����");
	set("long",
		"Ϊ�˽���¸ڹ������⣬�����֡���ʦ���ر��������"
		"��ʵ�������ﵱС��԰�Ļ�ũ��\n");
	set("str", 100);
	set_skill("unarmed", 50);
	set_skill("dodge", 50);
	set_temp("apply/damage", 15);

	set("combat_exp", 800000);
	set("attitude", "friendly");

	set("vendor_goods", ([
		__DIR__"obj/zhongzhi": 20,
	]));

	setup();
	set("chat_chance", 10);
	set("chat_msg", ({
		"��ũʮ�ֳϿҵ�˵���������Ǻð�����������ݹ�����\n",
		"��ũ̾�˿���˵���⹤���������ף��������ѣ�����ϲ�����������\n",
	}));

	carry_object("/clone/cloth/cloth")->wear();
	set_max_encumbrance(100000000);
}

void init()
{
	add_action("do_buy", "buy");
	add_action("do_list", "list");
}
