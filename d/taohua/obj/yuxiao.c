#include <ansi.h>
#include <weapon.h>

inherit XSWORD;

void create()
{
	set_name(HIW "����" NOR, ({"yu xiao", "xiao"}));
	set_weight(500);

	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "֧");
		set("long", "һ֧�������ɵĳ������ȥ��Ө�����������˾������������\n");
		set("value", 10000);
		set("icon", "05061");
		set("material", "stone");
		set("wield_msg", "$N����һ�ӣ������Ѷ���һ֧��Ө��������\n");
		set("unwield_msg", "$N��������һת��գ�ۼ�������Ȼ����Ӱ�١�\n");
	}
	init_xsword(45);
	setup();
}

int query_autoload() { return 1; }