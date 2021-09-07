// jialaoliu.c

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("������", ({ "jia laoliu", "jia" }));
	set("title", HIR "��ػ�"HIG"��ľ��"NOR"����");
	set("shen_type", 1);

	set("gender", "����");
	set("age", 35);
	set("long",
		"\n������ػ���ľ�û��ڣ�����������֮ʱ�����������ɣ�\n"+
		"�����ǲ���ɱ���췴��ֻ����˽©˰����û���ӵ�С���⣬\n"+
		"������������������׷ɱ��éʮ��Ҳ��˺���������\n");
	set("no_get_from", 1);

	set_skill("unarmed", 60);
	set_skill("dodge", 60);
	set_temp("apply/attack", 30);
	set_temp("apply/attack", 30);
	set_temp("apply/damage", 15);

	set("combat_exp", 50000);
	set("attitude", "friendly");
	set("chat_chance", 3);

	set("chat_msg", ({
		"��������Ȼ˵�������η�����ɶ�\n",
		"������˵: ������������Ҫ������ֵ�ߴ��кô�����\n",
		"������ͻȻ˵��: ������ǰ�ֵ��ڣ����е㽫�������\n",
	}));

	set("inquiry", ([
		"�½���" : "����ܶ����ɲ����װ���",
		"��ػ�" : "ֻҪ��Ӣ�ۺú���������������ػᡣ",
		"���帴��" : "ȥ�ײĵ�ͻش�����ϸ���ưɣ�",
		"����" : "�����£�",
		"�п�" : "�����£�",
	]));

	setup();
	carry_object("/clone/misc/cloth")->wear();
}
