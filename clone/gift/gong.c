#include <ansi.h>
#include <armor.h>

inherit "/clone/weapon/bow";

void create()
{
	set_name(HIY "点金盘龙弓" NOR, ({ "panlong gong", "gong", "bow" }));
	set_weight(1000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "张");
		set("value", 20);
		set("power", 250000);   // 攻击威力
		set("accuracy", 180);   // 准确度150%
		set("no_put", 1);
		set("no_get", 1);
		set("no_give", 1);
		set("no_drop", 1);
		set("no_steal", 1);
		set("no_beg", 1);
	}
	setup();
}

int query_autoload() { return 1; }