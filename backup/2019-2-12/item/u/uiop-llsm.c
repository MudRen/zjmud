// ITEM Made by player(������:uiop) /data/item/u/uiop-llsm.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Mon Feb 11 15:16:11 2019
#include <ansi.h>
#include <armor.h>

inherit ARMOR;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;33m����ʨ����[2;37;0m", ({ "llsm" }));
	set_weight(7500);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[37m�Ϲź���[2;37;0m���ƶ��ɵ�һ�Ż��ס�
ս�����ս���������������ף��������������Ϊ�ռ�����ʨ���ף������ȼײ��ԣ���������Ϊֻ�����������ԣ������ռ�����ʨ������[2;37;0m
����Ե�Ͽ���һ��С�֣�������(uiop)
");
	set("value", 1500000);
	set("point", 123);
	set("material", "steel");
	set("wear_msg", "$N����������£�ս����������ħ����ӥȮ���ȣ��������٣�����̳ǰ�����ɷ���񹦵�����ħ�������ս�޸ǣ�̫��ʥ�����Ƶ��ޱߣ�������������[2;37;0m\n");
	set("remove_msg", "[33m$N[33m������[1;33m����ʨ����[2;37;0m[33m��[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/parry", apply_armor() / 15 + 1);

	setup();
}

string long() { return query("long") + item_long(); }
