#include <ansi.h>
inherit ROOM;
int do_look(string arg);
void create()
{
	set("short", "ɽ��");
	set("long", @LONG
���ǻ�ɽ��ɽ�Ķ���ɽ�£����Ϸ����ǻ�ɽ����������Ⱥ�ľ��ң�����
�Ĵ������������ͷ����
LONG );
	set("exits",([
		"east":__DIR__"songlin4",
	]));
	setup();
}

void init()
{
	add_action("do_look", "look");
}

int do_look(string arg)
{
	object me = this_player(), inv;
	inv = present("kuihua baodian", me);

	if (arg == "window" || arg == "windows" || arg == "chuanghu" || arg == "chuang")
	{
		if (query("over"))
		  {
       	   	   tell_object(me,"һ�Ƚ����ŵĴ�����ûʲô���Ƶġ�\n");
			return 1;
		  }

		if (query("begin"))
		  {
       	   	   tell_object(me,"������������Ӱ����̸����Ҫ͵���ͱ𶯡�\n");
			return 1;
		  }	
		if (objectp(inv))
		  {
       	   	   tell_object(me,"�����Ѿ������ˣ����ǸϽ��뿪Ϊ�á�\n");
			return 1;
		  }	
		if (me->query("gender") != "����")
		  {
       	   	   tell_object(me,"����û��ǲ�Ҫ͵���ĺá�\n");
			return 1;
		  }		
		else
		{
			message_vision(HIB "$N" HIB "��������ȥ��ֻ����ǰ����������������Ӱ�����ڵ���ϸ�$N" HIB
					   "���Ͳ�ס���棬����\n"
					   "���ߵ���ǰ͵�����˵ĶԻ���"NOR"\n",me);
			remove_call_out("do_talk1");
			call_out("do_talk1", 4, me);
			set("begin",1);
			return 1;
		}
	 }
}

void do_talk1(object me)
{
	if (! objectp(me))
		return;

	message_vision(WHT "\nֻ����һλŮ�ӵ�����˵������ʦ�磬�Ҿ����������ɫ���ԣ��ǲ���������ϼ����\n"
			   "Щ���鷳���ɱ�̫�󾫽����ǳ������������������ƺ��ǻ�ɽ���ŷ���������"NOR"\n", me);
	remove_call_out("do_talk2");
	call_out("do_talk2", 4, me);
}

void do_talk2(object me)
{
	if (! objectp(me))
		return;

	message_vision(WHT "\n������һλ��������������˵������û�а���������˳���úܡ�����������ϡ���ǻ�ɽ\n"
			   "����������Ⱥ���㲻�����һ����"NOR"\n", me);
	remove_call_out("do_talk3");
	call_out("do_talk3", 4, me);
}

void do_talk3(object me)
{
	if (! objectp(me))
		return;

	message_vision(WHT "\n��Ů���ֵ�����������ң�Ϊ��ô�����˵����ɤ�ӱ��ˣ��ּ��ָߣ�����Ů���Ƶġ���"NOR"\n", me);
	remove_call_out("do_talk4");
	call_out("do_talk4", 4, me);
}

void do_talk4(object me)
{
	if (! objectp(me))
		return;

	message_vision(WHT "\n������ŭ��������˵�˵�����˵���������������ġ���"NOR"\n", me);
	remove_call_out("do_talk5");
	call_out("do_talk5", 4, me);
}

void do_talk5(object me)
{
	if (! objectp(me))
		return;

	message_vision(HIB "\n������������˵��仰��ɤ����Ȼ�൱�⣬ȷ���Ǹ�Ů���ڴ�Ƣ����"NOR"\n", me);
	remove_call_out("do_talk6");
	call_out("do_talk6", 4, me);
}

void do_talk6(object me)
{
	if (! objectp(me))
		return;

	message_vision(WHT "\n��Ů�ӽ���˵��������˵û�䣿��һ��֮�У��ʹ���û��������˵�����������򸾶��꣬\n"
			   "����������ô�ⲻ�����£��������ң���"NOR"\n", me);
	remove_call_out("do_talk7");
	call_out("do_talk7", 4, me);
}

void do_talk7(object me)
{
	if (! objectp(me))
		return;

	message_vision(WHT "\n�������ֵ���������ô�ⲻ�����£��ţ���ɽ֮�᲻Զ����������ͼ�̲����ɣ�������\n"
			   "Ȼ���ҡ���Ϊ�˷��ģ���Ҳ���еġ���"NOR"\n", me);
	remove_call_out("do_talk8");
	call_out("do_talk8", 4, me);
}

void do_talk8(object me)
{
	if (! objectp(me))
		return;

	message_vision(WHT "\n��Ů�Ӻ���һ�����������ҿ�����ֹ�ڴˡ���"NOR"\n", me);
	remove_call_out("do_talk9");
	call_out("do_talk9", 4, me);
}

void do_talk9(object me)
{
	if (! objectp(me))
		return;

	message_vision(WHT "\n�����Ӽ��������������Ϲ���ģ����������ô����"NOR"\n", me);
	remove_call_out("do_talk10");
	call_out("do_talk10", 4, me);
}

void do_talk10(object me)
{
	if (! objectp(me))
		return;

	message_vision(WHT "\n��Ů������ʮ��ƽ����˵��������˵�˳�������ɱ𷢻���֪������ԩ���˳������\n"
			   "�ճ�����˻��ԣ�������ֹѪ����֮ʱ�������������м����ģ�д�����֣��ƺ��ǽ���\n"
			   "֮�ࡣ�ڶ���������ҩ���Ǽ������Ѿ������ˣ���ʱ�����Ȼ����δ�ѡ����ʱ��֮�У�\n"
			   "�������Ҷ��ˣ����ޱ��˽�����������Ŀɲ������õġ���"NOR"\n", me);
	remove_call_out("do_talk11");
	call_out("do_talk11", 6, me);
}

void do_talk11(object me)
{
	if (! objectp(me))
		return;

	message_vision(WHT "\n�����Ӽ��β��˵��������ֻ���������˵��һ�����֣���û��˵��ȥ����"NOR"\n", me);
	remove_call_out("do_talk12");
	call_out("do_talk12", 4, me);
}

void do_talk12(object me)
{
	if (! objectp(me))
		return;

	message_vision(WHT "\n��Ů��������ת��ͣ�˵������ʦ�磬�һ�ɽһ�ɵĽ��������ж��������裬��ϼ��\n"
			   "���������ǲ������Դ��������ۣ����������������ڽ�����ԭ������ȥ��ѧ���ɽ�����\n"
			   "ֻ�ǽ���������Ұ�Ĵ�㣬ͼ�����ɡ���ɽһ���������˵��ôҲ����������������\n"
			   "�С�������������̩ɽ����ɽ����ɽ���ɣ���ʱ�����ɶ���һ�ɣ��ҿ�����ռ������Ӯ\n"
			   "�棬������Ĳ�ʤ������������ҵľ綷һ����������������ɽ��Ҳ�����ˣ����˾�\n"
			   "Ȫ֮��Ҳ�������Ի�ɽ�ɵ��������ڡ���"NOR"\n", me);
	remove_call_out("do_talk13");
	call_out("do_talk13", 6, me);
}

void do_talk13(object me)
{
	if (! objectp(me))
		return;

	message_vision(WHT "\n�����Ӵ�������������֪����ѧ��а�������㡭���㡭����͵�����𣿡�"NOR"\n", me);
	remove_call_out("do_talk14");
	call_out("do_talk14", 4, me);
}

void do_talk14(object me)
{
	if (! objectp(me))
		return;

	message_vision(WHT "\n��Ů��˵���������ֺα�͵�����֪������˵�������������Ѿ�ȫȻ���ˣ����˶�����\n"
			   "�������ѵ����Լ����������ã�ÿ���糿���㱻�������������������롭����"NOR"\n", me);
	remove_call_out("do_talk15");
	call_out("do_talk15", 4, me);
}

void do_talk15(object me)
{
	if (! objectp(me))
		return;

	message_vision(WHT "\n�����Ӽ��һ�����ʵ��������Ƽ��ˣ����������Ǿ�������"NOR"\n", me);
	remove_call_out("do_talk16");
	call_out("do_talk16", 4, me);
}

void do_talk16(object me)
{
	if (! objectp(me))
		return;

	message_vision(WHT "\n��Ů��̾�����������Ƽ��ˣ�һֱ��˵����ճ�ļ��룬���������ˣ�ȴ�����ù�������\n"
			   "�˼�ʮ����޵����֮�ˣ���"NOR"\n", me);
	remove_call_out("do_talk17");
	call_out("do_talk17", 4, me);
}

void do_talk17(object me)
{
	if (! objectp(me))
		return;

	message_vision(WHT "\n�����Ӽ����Ѱ�¶���޿��ٱ磬�������ã��ʵ��������˻���˭֪���ˣ���"NOR"\n", me);
	remove_call_out("do_talk18");
	call_out("do_talk18", 4, me);
}

void do_talk18(object me)
{
	if (! objectp(me))
		return;

	message_vision(WHT "\n��Ů��˵������û�У�ɺ����ƽ֮Ҳ��֪����"NOR"\n", me);
	remove_call_out("do_talk19");
	call_out("do_talk19", 4, me);
}

void do_talk19(object me)
{
	if (! objectp(me))
		return;

	message_vision(WHT "\n�����ӳ���Ƭ�̣�˵�������ã��������Ȱ��������ģ���������ȥ���������뷨����\n"
			   "����ϴˢ��ס���·���������Ҳ�����ˡ���"NOR"\n", me);
	remove_call_out("do_talk20");
	call_out("do_talk20", 4, me);
}

void do_talk20(object me)
{
	object book;

	if (! objectp(me))
		return;

	message_vision( HIR "\n$N���һ�������������ֹ�������˲���֮����������к�������������Ȩ��ȥ����\n"
			      "�ڴ�ʱ��ֻ���ô���ѽ��һ���򿪣�$N��æ��ͷ����ǰ���һ�����Ǽ�����Ʈ��������\n"
			      "���Ŵ����ּ����ϡ��ۿ������Ĵ�����Ʈ����$N����һץ���������ߣ�û��ץ������ʱ\n"
			      "$N��������֮���⣬���ִ������ϣ������������һ����ֻ���ż��ƺ����������ģ���\n"
			      "�������������������˵ý������������Ĺ����ˣ�û��������Ͽ�µ�������Ԩ�С�"NOR"\n", me);
	set("over", 1);
	me->set_temp("over", 1);
	message_vision(HIY "$N�õ�һ�����������䡷��"NOR"\n", me);
	book = new("/clone/book/kuihua");
	book->move(me, 1);
}
