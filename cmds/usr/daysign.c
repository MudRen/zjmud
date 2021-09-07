#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string *list,file;
	int i,last,times,pot;
	mapping gifts;
	object ob;

	gifts = ([
		"/clone/shizhe/book_tianfu":10,
		"/clone/shizhe/putao":10,
	]);

	last = me->query("last_day_sign");
	times = me->query("day_sign_times");
	if(time()/86400 == last/86400)
		return notify_fail("�������ǩ�����ˣ���Ŀǰ������ǩ����"+HIY+times+NOR+"���졣\n");

	if(times>=6)
	{
		tell_object(me,"�������һ��ǩ����\n");
		me->set("day_sign_times",6);
		times = 6;
	}
	if(time()/86400 - last/86400 > 1)
	{
		tell_object(me,"������û��ǩ����¼��������¼�ӽ��쿪ʼ��\n");
		times = 0;
	}

	me->set("last_day_sign",time());
	times += 1;
	me->set("day_sign_times",times);
	pot = random(1000) + 1000 + times*500;
	me->add("potential",pot);
	me->add("combat_exp",pot);
	tell_object(me,"������ǩ��"+HIY+times+NOR+"�Σ����"+HIY+pot+NOR+"�㾭���Ǳ�ܡ�\n");
	list = keys(gifts);
	for(i=0;i<sizeof(list);i++)
	{
		file = list[i];
		if((gifts[file]+times*10) > random(100))
		{
			ob = new(file);
			tell_object(me,"������"+ob->short()+"��\n");
			ob->move(me);
		}
	}
	return 1;
}

int help(object me)
{
	write(@HELP
ǩ��
HELP
	);
	return 1;
}
