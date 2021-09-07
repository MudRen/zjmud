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
        set_name(HIR"�������ĵ�"NOR, ({"huxin dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long","һ��"+name()+"������һ�����Ƶ�����ʥҩ����������������\n");
		set("unit", "��");
		set("base_unit", "��");
		set("base_weight", 1);
		//set("base_value", 1);
                set("no_put", 1);
                set("no_get", 1);
                //set("no_drop", 1);
                set("no_give", 1);
                set("no_sell", 1);
                set("no_steal", 1);
		set("only_do_effect", 1);
          }
   	setup();
}

int do_effect(object me)
{
      if(me->is_busy())
                return notify_fail("����æ���ء�\n");

	if (sizeof(filter_array(me->query_enemy(),(: userp :))))
		return notify_fail("���ں���Ҷ���ս��������ʹ��"+ name() +"��\n");

	if(me->query("combat_exp", 1) > 3000000) 
                return notify_fail("���Ѿ������ָ����ˣ�"+ name() +"�Ѿ�����ʧȥ�����ã�\n");

        if(me->query_condition("medicine") > 0 )
                  return notify_fail("���ϴε�ҩ������û���أ��Ȼ��ٳ԰ɡ�\n");


        if ( me->query("eff_qi") >= (me->query("max_qi")+me->query_gain_qi()) 
          && me->query("eff_jing") >= me->query("max_jing") 
          && me->query("neili") >= me->query("max_neili"))
                return notify_fail("�����ڲ���Ҫ��"+name()+"��\n");
          else {      
                me->set("eff_qi", me->query("max_qi")+me->query_gain_qi());
                me->set("eff_jing", me->query("max_jing"));

                me->set("neili",me->query("max_neili")*2);
                me->set("jingli",me->query("max_jingli"));
                me->set("food", me->max_food_capacity());
                me->set("water", me->max_water_capacity());
                me->apply_condition("medicine", 5);
                message_vision(HIG"$N����һ" + query("unit") + name() + HIG"����ʱ����Ȭ����"NOR"\n" , me);
	        if (query_amount() < 2) write("���"+ name() +"�����ˡ�\n");
              if ( me->is_fighting() ) me->start_busy(2);
	        add_amount(-1);
              return 1;
             }
        
}


