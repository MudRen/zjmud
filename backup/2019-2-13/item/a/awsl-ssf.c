// ITEM Made by player(��������:awsl) /data/item/a/awsl-ssf.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Thu Jan 10 20:56:23 2019
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;34mˮ�ַ�[2;37;0m", ({ "ssf" }));
	set_weight(3600);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[33m�ڽ�˿[2;37;0m���ƶ��ɵ�һ��ս�¡�
[1;34mһ�������Ķ���ˮ�ַ�����Ư��[2;37;0m
ս��Ե�Ͽ���һ��С�֣���������(awsl)
");
	set("value", 1500000);
	set("point", 154);
	set("material", "silk");
	set("wear_msg", "����[2;37;0m\n");
	set("remove_msg", "����[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
