inherit ITEM;
#include <ansi.h>

void create()
{
	set_name(HIM"��֬"NOR, ({"yan zhi"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("value", 100000);
		set("yuanbao", 100);
            set("no_sell",1);
		set("unit", "��");
		set("long","����һ����֬��ʹ��֮���������������ò��\n");
		set("only_do_effect", 1);
	}
}


int do_effect(object me)
{
      if (me->query("per")>29) return notify_fail("�����ò�Ѿ������ˡ�\n");

	me->add("per",1+random(3));

      if (me->query("per")>30) me->set("per",30);

	write(YEL"��ʹ����һ"+ query("unit") + name() +YEL"�������ò�����ˣ�"NOR"\n�����ڵ���ò�ǣ�"+me->query("per")+"��"NOR"\n");
	CHANNEL_D->do_channel( this_object(), "rumor","��˵"+me->query("name")+"ʹ����һ"+ query("unit") + name() +HIM"����ø���Ư���ˣ�");
	me->save();
	destruct(this_object());
	return 1;
}

int query_autoload() { return 1; }