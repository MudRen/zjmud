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
	set_name(HIM"��������"NOR,({"super box"}));
	if( clonep() )
		set_default_object(__FILE__);
	else
       {
	    set("long","���Ǵ��ڳ�ֵ�����ĳ������䣬��򿪿��������汦������Ŷ!\n");
            set("no_sell",1);
		set("unit", "��");
		set("base_unit", "��");
		set("base_weight", 10);
		set("base_value", 100);
		set("only_do_effect", 1);
	}
	setup();
}


int do_effect(object me)
{
	int i;
	int num=1;
	string obj=""; 
	object ob;

	//�������ǳ�������.����ϡ����ʯ,��֮��ʯ.
	string *box= ({
		"/clone/money/cash","/clone/gift/feimao","/clone/gift/feidan",
	});
  
	if (me->is_busy())
	      { write("����һ������δ��ɣ�\n"); return 1;}
	if( me->is_fighting() )
	      { write("ս���п����䣿����ѽ��\n"); return 1;}
       
	message_vision(HIM"$N�������["+this_object()->query("name")+"]�ĸ���,���仯Ϊһ����ɫ�⻪��"NOR"\n",me);
	i=random((int)sizeof(box));
    
	ob = new(box[i]); 
	if(ob->query("base_unit"))
	{
		num=1;
		ob->set_amount(num);
	}
	tell_object(me,""HIR"******************************************************\n");
	tell_object(me,""HIR"��ϲ: "NOR"���["+this_object()->query("name")+"]�еõ���..."+chinese_number(num)+ob->query("unit")+HIR+"<< "+ob->query("name")+HIR+" >>"+NOR+"\n");
	tell_object(me,""HIR"*****************************************************"NOR"\n");
	ob->move(me); 
	add_amount(-1);
	return 1;
}
