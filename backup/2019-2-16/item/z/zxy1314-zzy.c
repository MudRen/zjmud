// ITEM Made by player(�����:zxy1314) /data/item/z/zxy1314-zzy.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Wed Jan  2 10:22:15 2019
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit F_ITEMMAKE;

void create()
{
	set_name("����������[2;37;0m", ({ "zzy" }));
	set_weight(3600);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[33m�ڽ�˿[2;37;0m���ƶ��ɵ�һ��ս�¡�
���ױ鲼[2;37;0m
ս��Ե�Ͽ���һ��С�֣������(zxy1314)
");
	set("value", 1500000);
	set("point", 154);
	set("material", "silk");
	set("wear_msg", "����������ս����[2;37;0m\n");
	set("remove_msg", "����Ϣ��[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
