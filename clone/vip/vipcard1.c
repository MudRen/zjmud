inherit ITEM;
#include <ansi.h>

void create()
{
	set_name(HIR"VIP�쿨"NOR, ({"day card"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("value", 10000);
		set("yuanbao", 10);
		set("unit", "��");
		set("long","����һ��VIP�쿨��ʹ��֮������1���Աʱ��!\n");
        set("only_do_effect",1);
        set("no_sell",1);
	}
}

int do_effect(object me)
{
    int vip_time;
	
    vip_time=24 * 3600;
	
	write(YEL"��Ļ�Աʱ������1�죡"NOR"\n");
	me->add("zjvip/times",vip_time);
	me->save();
	destruct(this_object());
	return 1;
}

int query_autoload() { return 1; }
