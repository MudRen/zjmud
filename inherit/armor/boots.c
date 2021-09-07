// boots.c

#include <armor.h>

inherit EQUIP;

void setup()
{
	if (! clonep(this_object()))
		set("armor_type", TYPE_BOOTS);
set("armor_buwei", "�Ų�");
 if( !query("armor_apply/dodge") &&	 weight() > 3000 )
		set("armor_prop/dodge", - weight() / 3000 );

	::setup();
}

int washed(int n)
{
	switch (query("material"))
	{
	case "cloth":
		n += n * 3 / 10;
		break;
	case "leather":
		break;
	case "silk":
		n -= n * 3 / 10;
		break;
	case "bamboo":
		n -= n * 5 / 10;
		break;
	case "steel":
		n -= n * 7 / 10;
		break;
	}
	set_temp("no_wear", "����" + name() + "����ʪ�����ģ���û������\n");
	delete_temp("daub");
	remove_call_out("dry_cloth");
	if (n) call_out("dry_cloth", n);
	return n;
}

void dry_cloth()
{
	if (! objectp(this_object()))
		return;
	delete_temp("no_wear");
	message("vision", name() + "�Ѿ����ˡ�\n", environment());
}
