// huoxie.c ��Ы��

#include <ansi.h>

inherit POISON_INSECT;

void create()
{
	set_name("��Ы��", ({ "huo xie zi", "huo xie" }) );
	set_weight(220);
	set("race", "Ұ��");
	set("age", 2);
	set("long", "һֻ���ɫ�Ĵ�Ы�ӡ�\n");
	set("attitude", "peaceful");
	set("str", 20);
	set("con", 20);
	set("unit", "ֻ");
	set("limbs", ({ "ͷ��", "����", "��", "β��" }) );
	set("verbs", ({ "bite" }) );

	set("insect_poison", ([
		"level"  : 60,
		"maximum": 25,
	]));

	set("combat_exp", 100);

	setup();
}
