// ITEM Made by player(����:sun1903) /data/item/s/sun1903-yan.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Jan 22 22:17:06 2019
#include <ansi.h>
#include <armor.h>

inherit WAIST;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;32m����[2;37;0m", ({ "yan" }));
	set_weight(1440);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[33m�ڽ�˿[2;37;0m���ƶ��ɵ�һ��������
[1;32m�����°������ƵĿ�����������ֻ����һ�����ʼ��ѵ�ī����״���ƴֲ�ȴ���ӳ���[2;37;0m
����Ե�Ͽ���һ��С�֣�����(sun1903)
");
	set("value", 1500000);
	set("point", 61);
	set("material", "silk");
	set("wear_msg", "[33m$N[33mװ��[1;32m����[2;37;0m[33m��[2;37;0m\n");
	set("remove_msg", "[33m$N[33m������[1;32m����[2;37;0m[33m��[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
