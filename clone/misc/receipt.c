// receipt.c ��ִ

inherit ITEM;

int is_receipt() { return 1; }

void create()
{
	set_name("��ִ", ({ "receipt" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�Ż�ִ��\n");
		set("value", 1);
		set("no_sell", 1);
	}
	setup();
}
