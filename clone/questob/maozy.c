// maozy.c

inherit ITEM;

void create()
{
	set_name("è֮��", ({ "mao yan" }));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("no_sell", "��...����ʲô�������ҿɲ���Ҫ��\n");
		set("long", "�����һ��è�۱�ʯ����ΧǶ�Ž�ߡ�\n");
		set("value", 1);
		set("material", "stone");
	}
	setup();
}
