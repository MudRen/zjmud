// baoguo.c ����

inherit ITEM;

void create()
{
	set_name("����", ({ "baoguo", "bag" }));
	set_weight(300);
	set_max_encumbrance(10000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "һֻ��ϸ��֯�ɵĴ��ӣ��������װ������\n");
		set("value", 200);
	}
}

int is_container() { return 1; }
