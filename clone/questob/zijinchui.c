// zijinchui.c

inherit ITEM;

void create()
{
	set_name("�Ͻ�", ({ "zijin chui", "chui" }));
	set_weight(10000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�԰����Ͻ𴸣�������װ��Ʒ��\n");
		set("value", 4000);
		set("material", "copper");
	}
	setup();
}
