// baiyubi.c

inherit ITEM;

void create()
{
	set_name("�����", ({ "baiyu bi", "bi" }));
	set_weight(300);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "֧");
		set("long", "��Ө��͸�ĵĺ�������ĥ�ı������\n");
		set("value", 3000);
		set("material", "stone");
	}
	setup();
}
