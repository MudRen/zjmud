// ITEM Made by player(����:liuyiping) /data/item/l/liuyiping-jimie.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sat Jan  5 14:35:02 2019
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit F_ITEMMAKE;

void create()
{
	set_name("����[2;37;0m", ({ "jimie" }));
	set_weight(3600);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[33m�ڽ�˿[2;37;0m���ƶ��ɵ�һ��ս�¡�
��ɫ�ķ�����д��һ����������[2;37;0m
ս��Ե�Ͽ���һ��С�֣�����(liuyiping)
");
	set("value", 1500000);
	set("point", 154);
	set("material", "silk");
	set("wear_msg", "[1;37m��Χ�ĳ�����ƽ��������[2;37;0m\n");
	set("remove_msg", "[33m$N[33m�����˼���[2;37;0m[33m��[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }