// ITEM Made by player(������:m2376182530) /data/item/m/m2376182530-axns.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Dec 30 21:27:57 2018
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("����ŵ˹ս��[2;37;0m", ({ "axns" }));
	set_weight(9000);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[1;35m����[2;37;0m���ƶ��ɵ�һ������
��ԭ����һ���а���ŵ˹�Ķ�ħ��������������ɱ�����������������������������ս��ɢ����а�ܵ���Ϣ��[2;37;0m
�����Ͽ���һ��С�֣�������(m2376182530)
");
	set("value", 2100000);
	set("point", 220);
	set("material", "magic stone");
	set("wield_msg", "��ħ�����ˣ�����������$N�õ���[2;37;0m\n");
	set("unwield_msg", "$N��ս����������[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	init_sword(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
