// ITEM Made by player(�����:zxy1314) /data/item/z/zxy1314-zxy.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sat Dec 22 15:34:14 2018
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("��Ԩ[2;37;0m", ({ "zxy" }));
	set_weight(7500);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[37m�Ϲź���[2;37;0m���ƶ��ɵ�һ������
����������ţ�˻˻�Ʒ磬��������������������ʱ����ӯ���࣬�㽣����ʱ���������磬��Ҷ�ױ���[2;37;0m
�����Ͽ���һ��С�֣������(zxy1314)
");
	set("value", 1500000);
	set("point", 154);
	set("material", "steel");
	set("wield_msg", "��������һ��������������Ȫ����ն��а�Ĳ���[2;37;0m\n");
	set("unwield_msg", "�������Ƕ����Ĺ����պ硣[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	init_sword(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
