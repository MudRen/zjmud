// ITEM Made by player(������:m2376182530) /data/item/m/m2376182530-emzy.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Dec 18 21:46:53 2018
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit F_ITEMMAKE;

void create()
{
	set_name("��ħ֮��[2;37;0m", ({ "emzy" }));
	set_weight(1400);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[1;37m����˿[2;37;0m���ƶ��ɵ�һ��ս�¡�
�����˹Ŷ���֮­֮�������������˶�ħ��˫��[2;37;0m
ս��Ե�Ͽ���һ��С�֣�������(m2376182530)
");
	set("value", 2100000);
	set("point", 220);
	set("material", "silk");
	set("wear_msg", "��ڵ������Ĵ��ţ�ʮ�ֵĲ����֡�[2;37;0m\n");
	set("remove_msg", "$N�������պá�[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
