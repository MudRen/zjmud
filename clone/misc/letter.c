// letter.c ��ִ

inherit ITEM;

int is_letter() { return 1; }

void create()
{
	set_name("�ż�", ({ "letter" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ���ţ�\n");
		set("value", 0);
	}
	setup();
}
