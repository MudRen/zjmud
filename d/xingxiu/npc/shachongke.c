//  poison: shachongke.c
// Jay 3/17/96

inherit ITEM;

void create()
{
	set_name("ɳ���", ({"shachong ke", "ke"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "ֻ");
		set("long", "����һֻɳ��ĸɿǣ����Ʊ���ҩ��ԭ�ϡ�\n");
		set("value", 300);
	}

	setup();
}
