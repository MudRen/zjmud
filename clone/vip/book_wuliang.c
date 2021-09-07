
#include <ansi.h>

inherit COMBINED_ITEM;

string query_autoload() { return query_amount() + ""; }

void autoload(string param)
{
	int amt;

	if (sscanf(param, "%d", amt) == 1)
		set_amount(amt);
}

void setup()
{
	set_amount(1);
	::setup();
}

void create()
{
	set_name("��������", ({"kungfu book"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "��������ѧ�ĵõ�һҳ�о�\n");
		set("unit", "ҳ");
		set("base_unit", "ҳ");
		set("base_weight", 10);
		set("base_value", 10000);
		set("yuanbao", 10);
        set("no_sell", 1);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
      int exp2;

      if (me->is_busy())
                return notify_fail("����æ���ء�\n");

	if (me->is_fighting())
		    return notify_fail("����ս���У�����ʹ��"+ name() +"��\n");

      if ((me->query("experience")-me->query("learned_experience"))>50000)
                return notify_fail("���ʵս����Ѵﵽһ��ƿ����Ŀǰ���ʺ��Ķ�"+ name() +"��\n");
      else {
                exp2=1400+random(201);
                me->add("experience",exp2);

                message_vision("$N��ϸ�ж���һ" + query("unit") + name() + "��ֻ��һ�������ඥ����ʱ��Ȼ���ʡ�\n", me);
	          write(YEL"��ϲ���������"+exp2+"��ʵս��ᡣ"NOR"\n");

	          add_amount(-1);
                return 1;
            }

}
