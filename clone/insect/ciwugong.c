// ciwugong.c ������

#include <ansi.h>

inherit POISON_INSECT;

void create()
{
	set_name(RED "������" NOR, ({ "chiban wu gong", "wugong" }) );
	set_weight(120);
	set("race", "Ұ��");
	set("age", 3);
	set("long", "һֻ�����˺�ɫ�ߵ����򼣬���ǹ��졣\n");
	set("attitude", "peaceful");
	set("str", 22);
	set("con", 25);
	set("unit", "ֻ");
	set("limbs", ({ "ͷ��", "����" }) );
	set("verbs", ({ "bite" }) );

	set("insect_poison", ([
		"level"  : 72,
		"maximum": 50,
	]));

	set("combat_exp", 3000);

	setup();
}
