// zhizhu.c

#include <ansi.h>
inherit NPC;
void create()
{
    set_name(HIR"���"NOR, ({ "wu gong" }));
    set("long", "һֻ�ж��Ļ��ɫ����򼡣\n");

    set("race", "Ұ��");
    set("age", 3);
    set("attitude", "aggressive");

    set("max_ging", 80);
    set("max_qi", 80);
    set("str", 10);
    set("cor", 50);

    set("limbs", ({ "��","����", "����", "β��"}));
    set("verbs", ({ "bite" }) );

    set_temp("apply/attack", 10);
    set_temp("apply/damage", 10);
    set_temp("apply/armor", 10);

    set("combat_exp", 1000);
    setup();
}

int hit_ob(object me, object ob, int damage)
{
	if (random(damage) > (int)ob->query_temp("apply/armor") &&
	    ob->affect_by("poison", ([ "level" : random(10) + 10,
				       "name"  : "��򼶾",
				       "id"    : "nature poison",
				       "duration" : 5 + random(10), ])))
	{
		tell_object(ob, HIG "��е������ñ�����"NOR"\n" );
	}
}
