// ITEM Made by player(������:m2376182530) /data/item/m/m2376182530-zkdm.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Jan 20 22:59:59 2019
#include <ansi.h>
#include <armor.h>

inherit WAIST;
inherit F_ITEMMAKE;

void create()
{
	set_name("[2;37;0m[35m������ķ[2;37;0m", ({ "zkdm" }));
	set_weight(1440);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[33m�ڽ�˿[2;37;0m���ƶ��ɵ�һ��������
[1;36mԭ����һֻ����[35m������ķ[1;36m�ĵ���Ȯ��������������ܺ󣬱����������һ��װ����[2;37;0m
����Ե�Ͽ���һ��С�֣�������(m2376182530)
");
	set("value", 1500000);
	set("point", 61);
	set("material", "silk");
	set("wear_msg", "����Ȯ�����ŵ����ˡ�[2;37;0m\n");
	set("remove_msg", "������ķ�Ѳ��ٻԻ͡�[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
