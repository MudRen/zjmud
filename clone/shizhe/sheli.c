// sl_cloth.c

#include <ansi.h>

inherit ITEM;

string setcolor();

void create()
{
        set_name(HIW"ʥ"HIG"��"HIB"��"HIR"��"NOR, ({"sheli zi", "sheli"}));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
		set("text" , "����һ��ǰ����ɮ���µ�ʥ�����ӣ���"ZJURL("cmds:xu neili")+ZJSIZE(20)+"ע��"NOR"(xu neili)��"ZJURL("cmds:xi neili")+ZJSIZE(20)+"��ȡ"NOR"(xi neili)�Ĺ�Ч��"NOR"\n");
		set("long",HIW+query("text") );
                set("value", 8000);
                set("no_put", 1);
                set("no_get", 1);
                set("no_drop", 1);
                set("no_give", 1);
                set("no_sell", 1);
                set("no_steal", 1);
                set("material", "stone");
		set("neili",130000);
        }
        setup();
}

void init()
{
	add_action("do_zhuru","xu");
	add_action("do_xiqu","xi");
}

int do_zhuru(string arg)
{
	int cost,max_neili;
	object me = this_player();
        max_neili=130000;

	if (arg!="neili")
		return notify_fail("��Ҫ����ʲô?\n");

	if( query("neili") >= max_neili )
		return notify_fail(""HIW"ʥ"HIG"��"HIB"��"HIR"��"NOR"���Ѿ�������ӯ�����޷��������������\n");

	if( me->query_skill("force") < 200 )
		return notify_fail("����ڹ��ȼ��������޷���"HIW"ʥ"HIG"��"HIB"��"HIR"��"NOR"������������\n");

	cost = 11000;

	if( cost > me->query("neili") )
		return notify_fail("����������㣬�޷���"HIW"ʥ"HIG"��"HIB"��"HIR"��"NOR"�������㹻��������\n");

	add("neili",10000);
	if (query("neili") > max_neili) set("neili",max_neili);
	me->add("neili" , -cost);

	//message_vision(HIC"$N"HIC"Ǳ���ڹ���˫���鰴"HIW"ʥ"HIG"��"HIB"��"HIR"��"HIC"���������������С�"NOR"\n",me);
      tell_object(me,HIC"��Ǳ���ڹ���˫���鰴"HIW"ʥ"HIG"��"HIB"��"HIR"��"HIC"���������������С�"NOR"\n");	
	setcolor();

	return 1;
}

int do_xiqu(string arg)
{

	object me = this_player();

	if (arg!="neili")
		return notify_fail("��Ҫ��ȡʲô?\n");

        if(me->query_temp("dgjj/zongjue"))
		return notify_fail("��Ŀǰ���ж��¾Ž��ġ��ܾ�ʽ�����޷���"HIW"ʥ"HIG"��"HIB"��"HIR"��"NOR"����ȡ������\n");

	if( query("neili") <10000 )
		return notify_fail(""HIW"ʥ"HIG"��"HIB"��"HIR"��"NOR"�д���������Ѿ����Ĺ��ˣ�\n");

	if( me->query_skill("force") < 100 )
		return notify_fail("����ڹ��ȼ��������޷���"HIW"ʥ"HIG"��"HIB"��"HIR"��"NOR"����ȡ������\n");

	if (me->query("neili") > me->query("max_neili"))
		return notify_fail("��Ŀǰ�������棬�����"HIW"ʥ"HIG"��"HIB"��"HIR"��"NOR"����ȡ������\n");

	if (sizeof(filter_array(me->query_enemy(),(: userp :))))
		return notify_fail("���ں���Ҷ���ս��������ʹ��"HIW"ʥ"HIG"��"HIB"��"HIR"��"NOR"��\n");

        if(me->query_condition("medicine") > 0 )
                  return notify_fail("��ոմ�"HIW"ʥ"HIG"��"HIB"��"HIR"��"NOR"����ȡ����������Ⱦ�����Ӧ��֮������ٴ���ȡ��\n");

	add("neili",-100);

        me->set("neili",me->query("max_neili")*2);
        if (me->query_condition("fire_poison")) me->clear_condition("fire_poison");
        if (me->query_condition("huagu")) me->clear_condition("huagu");
	  me->set_temp("nopoison", 1);
        me->apply_condition("medicine", 4);

        tell_object(me,HIC"��˫���鰴"HIW"ʥ"HIG"��"HIB"��"HIR"��"HIC"��������ȡ������������"NOR"\n");	

        if( me->is_fighting() )
                me->start_busy(2);

	setcolor();

	return 1;
}


string setcolor()
{
	int lvl;
	string color , s;

	if ( query("neili") != 0 )
		lvl = query("neili") / 10000;
	else
		lvl = 0;
	switch (lvl)  {
		case  0:
		case  1:
		case  2: color = HIW;break;
		case  3:
		case  4: color = HIC;break;
		case  5:
		case  6: color = CYN;break;
		case  7:
		case  8: color = HIB;break;
		case  9:
		case 10: color = BLU;break;
		case 11:
		case 12: color = HIM;break;
		case 13: color = MAG;break;
		default: color = HIW;
	}
	set("name" , HIW"ʥ"HIG"��"HIB"��"HIR"��"NOR );
	
	if( lvl > 0 )
		s = HIW"ʥ"HIG"��"HIB"��"HIR"��"+color+"֮���Ѿ�����"+CHINESE_D->chinese_number(lvl)+"��������"NOR"\n";
	else
		s = "";
	set("long" , color+query("text")+s);

	return color;
}

int query_autoload() { return 1; }