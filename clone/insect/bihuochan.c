// bihuochan.c �̻����

#include <ansi.h>

inherit POISON_INSECT;

void create()
{
	set_name(HIG "�̻����" NOR, ({ "bihuo chanchu" }) );
	set_weight(320);
	set("race", "Ұ��");
	set("age", 3);
	set("long", "һֻ��󡣬������һ��������ɫ���ơ�\n");
	set("attitude", "peaceful");
	set("str", 25);
	set("con", 25);
	set("unit", "ֻ");
	set("limbs", ({ "ͷ��", "����", "����" }) );
	set("verbs", ({ "bite" }) );

	set("insect_poison", ([
		"level"  : 80,
		"maximum": 50,
	]));

	set("combat_exp", 8000);

	setup();
}
