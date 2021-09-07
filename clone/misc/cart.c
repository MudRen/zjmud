// cart.c
//

#include <ansi.h>

inherit ITEM;
inherit F_TRANSPORT;

void create()
{
	set_name("��", ({ "cart" }) );
	set_weight(200000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("value", 1);
		set("long", "����һ����ͨ�Ļ�����\n");
		set("no_sell", "�㻹���õ����ȥ�ɡ�\n");
		set("unit", "��");
		set("material", "wood");
		set("no_get", "�üһ����Ҳ�뿸�ڼ��ϣ�\n");
	}
	setup();
}

string long()
{
	mapping goods;
	string desc;

	desc = ::long();
	if (! mapp(goods = query_temp("goods")))
		return desc;

	desc += "����װ��" + chinese_number(goods["amount"]) +
		goods["unit"] + goods["name"] + "��\n";
	return desc;
}
