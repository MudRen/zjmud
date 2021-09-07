// Object: /clone/herb/candle.c ���ĺ�������
// Date: Mar. 3 2002 by Pound
/*
   ���ĺ��������ȼ֮�󣬷����Ķ������޳�ζ����������
   ��ɫ�޳�����Ӱ���٣��پ���ϸ�ĵ���Ҳ�������ˣ���֪����֮�䣬�����ж�������
   ���������ĺ���������������ʹ���ĴΡ�
   ��ȼ���򣬿��Ե��������ڳ������ж����������������������õĿ��Բ�����������ʱʧ����
   ���ﶾ��̫���Ե������ڵ�֮���ס�������������á�
*/

#include "/clone/herb/herb.h"
int do_dian(string arg);
int do_qu(string arg);
int do_fang(string arg);
string long_desc();

void create()
{
	set_name(HIY "����" NOR, ({"haitang candle", "candle"}));
	if (clonep())
	    set_default_object(__FILE__);
	else 
	{
	    set("base_unit", "��");
	    set("long", (: long_desc :));
	    set("no_sell", 1);	
	    set("base_value", 200000);
	    set("no_drop", 1);
	    set("no_steal", 1);
	    set("no_beg", 1);
//	  set("poison_type", "haitang_posion");
	    set("base_weight", 60);
	}		   
	setup();
}

string long_desc()
{
	string descrp;
	object ob;
	ob = this_player();
	descrp = HIY "���Ǹ�ϸС���µ�����" NOR;

// ͨ��look candle���Ի�ȡ������ʹ�õĴ�����
	if (ob->query("yaowang/candle/using") == 1)
	    descrp += YEL "�Ѿ���������������ȥֻ������һ�Ρ�"NOR"\n";
	else if (ob->query("yaowang/candle/using") == 2)
		descrp += YEL "��Լ��һ��೤������ȥ���������������ġ�"NOR"\n";
	else if (ob->query("yaowang/candle/using") == 3)
		descrp += YEL "���ȴ�Լ��һ����㣬����Ҳ�ò��˼��Ρ�"NOR"\n";
	else if (ob->query("yaowang/candle/using") == 4)
		descrp += YEL "��Լ�ж���೤��ǡ����߬�������"NOR"\n";
	else
	    descrp += YEL "��������ȥ����������⣬�������ʦ�ɡ�"NOR"\n";
	return descrp;
}

void init()
{   
	add_action("do_dian", "dian"); 
	add_action("do_qu", "qu"); 
}

int do_qu(string arg)
{
	object me;
	me = this_player();

	if (! arg || ! id(arg))
	    return notify_fail("����Ҫȡʲô��\n");
	if (me->is_busy())
	    return notify_fail("�㻹����æ����ȡ�����ɣ�\n");

	if (arg == "candle" || arg == "haitang candle")
	{
	    if (me->query_temp("qu_candle"))
		return notify_fail("���Ѿ�������ȡ�����ˡ�\n");
	    message_vision("$NС������شӻ���ȡ��һ��ϸС������\n", me);
	    me->set_temp("qu_candle", 1); 
// ���ĺ��������Էǳ��Ե����������˶������ơ��˴�����quָ���Ϊ��������Χ�˵�ע�⣬ֻҪ����robot�����л������ܡ�
// ���⣬�����޸�go.c�����϶�qu_candle���жϣ���ʾ���������ߡ�
	    me->start_busy(1 + random(2));
	    add_action("do_fang", "fang");	  
	}
	return 1;
}

int do_fang(string arg)
{
	object me;
	me = this_player();

	if (! arg || ! id(arg))
	    return notify_fail("����Ҫ��ʲô��\n");
	if (me->is_busy())
	    return notify_fail("�㻹����æ���ٷŶ����ɣ�\n");

	if (arg == "candle" || arg == "haitang candle")
	{
	    if (! me->query_temp("qu_candle"))
		return notify_fail("������û������\n");
	    message_vision("$NС������ذ�����Żص����\n", me);
	    me->start_busy(1 + random(2));
	    me->delete_temp("qu_candle"); 
	}
	return 1;
}

int do_dian(string arg)
{
	object me;
	me = this_player();

	if (! arg || ! id(arg))
	    return notify_fail("����Ҫ��ȼʲô��\n");
	if (me->is_busy())
	    return notify_fail("�㻹����æ���ٵ㶫���ɣ�\n");

	if (arg == "candle" || arg == "haitang candle")
	{
	    if (environment(me)->query("no_fight") || environment(me)->query("outdoors") == "city")
		return notify_fail("�������������˻�����ǲ�ġ�\n");
	    if (! me->query_temp("qu_candle"))
		return notify_fail("������û������\n");
	    message_vision(HIY "$NС������ص�ȼ�����е���������������������ҡҷ������������"NOR"\n", me);
	    me->start_busy(1 + random(2));
	    me->add("yaowang/candle/using", -1); 
	    remove_call_out("do_effect");
	    call_out("do_effect", 2, me); // ������������Ч�á������ֿ����ܵĻ��ᣬ�ȽϹ�ƽЩ��
	}

	return 1;
}

int do_effect(object me, object target)
{
	object *ob;
	int i;

	ob = all_inventory(environment(me));
	for(i = 0; i < sizeof(ob); i++) 
	{
	    if (! living(ob[i]) || ob[i] == me)
		continue;

	    me->want_kill(ob[i]);
	    ob[i]->kill_ob(me);

// ��ȼ���򣬿��Ե��������ڳ������ж����������������������õĿ��Բ�����������ʱʧ����
	    if (random((int)ob[i]->query("neili")) < 6000)
	    {
		message_vision(HIB "$N" HIB "˫ϥ������������������������������Ц��Ц�����鼫�ǹ��졣"NOR"\n", ob[i]);
		ob[i]->set_temp("die_reason", "����ʱ������ʼ�մ���΢Ц���ƺ�ʮ��ƽ��ϲ��");
		tell_object(ob[i], "��ͻȻ�о���Χ�����������Լ���ȥ����֪����֮�䣬�����������涾��\n");
		ob[i]->die();
	    }
	    else
	    {
		tell_object(ob[i], "��о���Щ�������Һ�����������Բ�������˫Ŀ��Ȼ���ܲ�ס������ä�ˣ�\n");
		message_vision(HIB "$N" HIB "˫���ڿ�����ץ���ˣ������������鼫�ǿֲ���"NOR"\n", ob[i]);
		ob[i]->set_temp("block_msg/all", 1);
	    }

	}

// �ж������Ƿ������ã�����޷�������destruct��
	if (me->query("yaowang/candle/using") < 1) 
	{
	    me->delete("yaowang/candle");
	    message_vision(HIY "$N���е�����㵽�˾�ͷ��ֻ������һ���������º죬һ�������������Ϩ���ˡ�"NOR"\n", me);
	    destruct(this_object());
	}
	else message_vision(HIY "һ��紵�˹�����$N���е��������һ������ʱϨ�ˡ�"NOR"\n", me);

	return 1;

}