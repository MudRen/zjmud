//yayifu.c

#include <armor.h>

inherit CLOTH;

void create()
{
	set_name("���۷�", ({"yayi fu", "cloth"}));
	set_weight(2000);
	if (clonep())
		set_default_object(__FILE__);
	else 
	{
		set("long",
		"һ����ɫ��װ��Ƕ�Ժ�ߣ��ǳ����������۴��ģ�\n");
		set("material", "cloth");
		set("unit", "��");
		set("value", 500);
		set("armor_prop/armor", 10);
	}

	setup();
}
