// Object: /clone/herb/haitang.c ���ĺ���
// Date: Feb . 3 2002 by Pound
// ÿ�����ĺ��Ŀ���ʹ���ĴΣ��ֱ��ǻ���Ҷ�����������������ˣ���ʹ�׹����⣬�ɽ����°ٶ���
// ����������ˣ���ô�پ���ϸ�ĵ���Ҳ�������ˣ���֪����֮�䣬�����ж�������
// ���ĺ��Ŀ���ֱ���������ˣ����������Ժ����������ҩ�����ƶ�ҩ��Ҫ�����ذ�æ��
// ����������һЦ���������⻨�ĸ�����Ҷ�������涾�ޱȣ��������������������ˡ���ֻҪ��ȥ�������������ˡ���
// ���Ц�������㵱����ţ��ô����������������

#include "/clone/herb/herb.h"
int do_eat(string arg);

void create()
{
	set_name(RED HBGRN "���ĺ���" NOR, ({"qixin haitang", "haitang"}));
	if (clonep())
	    set_default_object(__FILE__);
	else 
	{
	    set("base_unit", "��");
	    set("long", HIY "�������֦�ɶ�������֦���������������߸�СС�ĻƵ㡣"NOR"\n");
	    set("no_sell", 1);	
	    set("base_value", 200000);
	    set("no_give", 1);
	    set("no_drop", 1);
	    set("no_steal", 1);
	    set("no_beg", 1);
//	  set("poison_type", "haitang_posion");
//	  set("can_drug", 1);
	    set("base_weight", 90);
	}		   
	setup();
}

void init()
{   
	add_action("do_eat", "eat");   
	add_action("do_use", "use"); 
}

int do_eat(string arg)
{
	object me;
	me = this_player();

	if (! arg || ! id(arg))
	    return notify_fail("��Ҫ��ʲô��\n");
	message_vision(name() + "�������ˣ�$N�̲�ס���������˼��ڡ�\n\n", me);
	message_vision(HIB "$N" HIB "�о���Χ���������Լ���ȥ��˫ϥ������������������������"NOR"\n", me);
	me->set_temp("die_reason", "����ʱ������ʼ�մ���΢Ц���ƺ�ʮ��ƽ��ϲ��");
// Ŀǰ��ϵͳ��ǰ�������ǡ������ڵ��������˼��£���һ�죬�������������Ѫ�����ˣ���������Ҫ��Ѫ��

	me->die();
	destruct(this_object());
	return 1;
}

int do_use(string arg)
{
	object me, ob;
	string what, target;
	mapping my;

	me = this_player();
	if (! arg || sscanf(arg, "%s to %s", what, target) != 2)
	    return notify_fail("���ĺ��ľ��˵�ʹ�÷���Ϊ��use ���Ĳ�λ���� to Ŀ��Ӣ��ID����\n");

	if (sscanf(arg, "%s to %s", what, target) == 2)
	{
	    if (what != "jing" && what != "��" && what != "gen" && what != "��" &&
		what != "ye" && what != "Ҷ" && what != "hua" && what != "��") 
		return notify_fail("���ܵ�����������ĺ��ĵ��Ĳ��ְɣ�����Ҷ����������\n");
	    ob = present(target, environment(me));
	    if (! objectp(ob = present(target, environment(me)))) 
		return notify_fail("����Ҫ�����ĺ��ľ�˭��\n");
	    if (me->is_busy())
		return notify_fail("�����ȵ���æ���پ��˰ɣ�\n");

	    if (what == "ye" || what == "Ҷ") 
	    {
		if (me->query("yaowang/qxht/ye"))
		    return notify_fail("���ĺ��ĵ�Ҷ���Ѿ������õ��ˡ�\n");
		message_vision("$N�����ĺ��ĵ�Ҷ��ժ�������������ˣ�����" + ob->query("name") + "���ϡ�\n", me);
		me->set("yaowang/qxht/ye", 1);
		ob->set_temp("nopoison", 3);
		me->add("yaowang/qxht/using", 1);
//	      ob->clear_condition(); // Ҷ�ӽ������涾���˴�ʹ����Doing��Ƶı��nopoison�ⶾ��
		ob->receive_damage("qi", (200 + random(100))); // ��ʹ
		message_vision(HIR "һ���ʹ����" + ob->query("name") + "�������ڵ������Ѿ�ȫ��ɢȥ�ˡ�"NOR"\n", me);
		me->start_busy(2 + random(3));
		me->receive_damage("jing", (66 + random(33)));
		return 1;
	    }

	    if (what == "hua" || what == "��") 
	    {
		if (me->query("yaowang/qxht/hua"))
		    return notify_fail("���ĺ��ĵĻ��Ѿ������õ��ˡ�\n");
		message_vision("$N�����ĺ��ĵĻ�ժ�������������ˣ�Ϳ��" + ob->query("name") + "����Ѩλ�ϡ�\n\n", me);
		message_vision(CYN + ob->query("name") + "ֻ��������Ѩλһ�����飬ȫ����Ѫ��ӯ��������������֮����"NOR"\n", me);
		me->set("yaowang/qxht/hua", 1);
		me->add("yaowang/qxht/using", 1);
		my = ob->query_entire_dbase(); // ��ʹ��Ѫȫ������ʱ���������ӱ���
		my["eff_jing"] = my["max_jing"];
		my["jing"] = my["max_jing"];
		my["eff_qi"] = my["max_qi"];
		my["qi"] = my["max_qi"];
		my["jingli"] = my["max_jingli"] * 2;
		my["neili"] = my["max_neili"] * 2;
		me->start_busy(2 + random(3));
		me->receive_damage("jing", (66 + random(33)));
		return 1;
	    }
// ���� �� �� ���������������ҩ�������������书�� ������ϴ�ͨ�ζ�������
// ÿ��ʹ�ý����д��ʹ�������ϣ�������Ҷ��������ȫ��ʹ����Ϻ�destruct haitang����ɾ��ʹ�������ϵı�ǡ�
//		me->delete("yaowang/qxht);
//		destruct(this_object());
// Create�����Ѿ�����˸��ַ�����ʩ���������ĺ����뿪ʹ���ߵ��µı�ǻ��ҡ�

	    if (what == "jing" || what == "��") 
	    {
		if (me->query("yaowang/qxht/jing"))
		    return notify_fail("���ĺ��ĵľ��Ѿ������õ��ˡ�\n");
		if (! me->query("yaowang/qxht/hua") || ! me->query("yaowang/qxht/ye"))
		    return notify_fail("���ĺ��ĵĻ���Ҷ����û�ã������ʹ�þ�������Ҷ��Ҫ�˷��ˣ�\n");
// ȡ����ֲ��ľ�������Ҷ��Ȼ���ή���޷�ʹ���ˡ���˼�������жϡ�
		message_vision("$N�����ĺ��ĵľ��������������������ˣ�����" + ob->query("name") + "���ϡ�\n", me);
		me->set("yaowang/qxht/jing", 1);
		ob->set_temp("nopoison", 3);
		me->add("yaowang/qxht/using", 1);
//	      ob->clear_condition(); // �������涾���˴�ʹ����Doing��Ƶı��nopoison�ⶾ��
		ob->receive_damage("qi", (200 + random(100))); // ��ʹ
		message_vision(HIR "һ���ʹ����" + ob->query("name") + "�������ڵ������Ѿ�ȫ��ɢȥ�ˡ�"NOR"\n", me);
		me->start_busy(2 + random(3));
		me->receive_damage("jing", (99 + random(33)));
		return 1;
	    }

	    if (what == "gen" || what == "��") 
	    {
		if (me->query("yaowang/qxht/gen"))
		    return notify_fail("���ĺ��ĵĸ��Ѿ������õ��ˡ�\n"); // ��������жϲ�����Ҫ��
		if (! me->query("yaowang/qxht/hua") || ! me->query("yaowang/qxht/ye") || ! me->query("yaowang/qxht/jing"))
		    return notify_fail("�����ʹ�ø������ĺ��ĵĻ���Ҷ�;���Ҫ�˷��ˣ�\n");
// ȡ����ֲ��ĸ�������Ҷ�;���Ȼ���ή���޷�ʹ���ˡ���˼�������жϡ�
		message_vision("$N�����ĺ��ĵĸ������������øɾ��������������ˣ�����" + ob->query("name") + "���ϡ�\n", me);
		me->set("yaowang/qxht/gen", 1);
		ob->set_temp("nopoison", 3);
		me->add("yaowang/qxht/using", 1);
		me->delete("yaowang/qxht");
//	      ob->clear_condition(); // �������涾���˴�ʹ����Doing��Ƶı��nopoison�ⶾ��
		ob->receive_damage("qi", (20 + random(10))); // ��ʹ���˴���Ƹ���������΢�º�Щ��
		message_vision(HIR "һ����΢����ʹ����" + ob->query("name") + "�������ڵ������Ѿ�ȫ��ɢȥ�ˡ�"NOR"\n", me);
		me->start_busy(2 + random(3));
		destruct(this_object());
		me->receive_damage("jing", (166 + random(33)));
		return 1;
	    }

	}
	return 1;
}
