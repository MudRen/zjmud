// combine.c

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object obj,target,*obs;
	int i,num,need;
	string item;
	mapping *needs;

	if (!arg)
		return notify_fail("��Ҫ�ϲ�ʲô��Ʒ��\n");



	if(sscanf(arg,"%s %d",item,num)!=2)
	{
		if (!objectp(obj=present(arg,me)))
			return notify_fail("��Ҫ�ϲ�ʲô��Ʒ��\n");

		message_vision(HIM "$N" HIM "��һЩ"+obj->query("name")+"����һ��Ĭ����ͨʹ���Ǳ仯��"NOR"\n", me);
		me->start_busy(1);

		if(obj->query("can_be_enchased")&&arrayp(needs=obj->query("enchased_need")))
		{
			obs = ({});
			for(i=0;i<sizeof(needs);i++)
			{
				if(!objectp(present(needs[i]["id"],me)))
					return notify_fail("������ȱ�ٺϳɸ��߼���Ʒ�������"+needs[i]["name"]+"��\n");
				obs += ({ present(needs[i]["id"],me) });
			}
			if (me->query("max_jingli") < 6000)
			{
				message_vision(HIG "���˰��죬�ƺ�û���κα仯��$N" HIG "һ���㬡�\n", me);
	       			return notify_fail(HIR "��о���ľ�����Ϊ��ԶԶ��������" HIR "�������⼸����Ʒ��\n");
			}

			for(i=0;i<sizeof(obs);i++)
			{
				obs[i]->add_amount(-1);
			}
			target = new(obj->query("can_be_enchased"));
			obj->add_amount(-1);
			target->move(me);
			write("��ϲ��������һ��"+target->query("name")+"��\n");
			if(target->query("id") == "god eyes")
			{
				// ������Ϣ
   		    		CHANNEL_D->do_channel(this_object(), "rumor","��˵" + me->name() + "���������ϱ�ʯ" + target->name() + HIM + "��");
		     		me->add("max_jingli", -5000);
			}

			return 1;
		}

		if(!obj->query("can_be_enchased")||!(need=obj->query("enchased_need"))||!obj->query_amount())
			return notify_fail(obj->query("name")+"�����ں����ɸ߼���Ʒ��\n");

		if(need>obj->query_amount())
			return notify_fail("����Ҫ"+need+obj->query("base_unit")+obj->query("name")+"�����ںϳ�һ���߼���Ʒ��\n");

		write(INPUTTXT("�������ɶ��ٸ�"+(obj->query("can_be_enchased"))->query("name")+"��"ZJBR
			"�����������룺"+obj->query_amount()/need,"combine "+arg+" $txt#\n"));
		return 1;
	}

	if (!objectp(obj=present(item,me)))
		return notify_fail("��Ҫ�ϲ�ʲô��Ʒ��\n");

	if(!obj->query("can_be_enchased")||!(need=obj->query("enchased_need"))||!obj->query_amount())
		return notify_fail(obj->query("name")+"�����ں����ɸ߼���Ʒ��\n");

	if(need>obj->query_amount())
		return notify_fail("����Ҫ"+need+obj->query("base_unit")+obj->query("name")+"�����ںϳ�һ���߼���Ʒ��\n");

	if(num<1||(num*need)>obj->query_amount())
		return notify_fail("���ںϲ�����ô���"+(obj->query("can_be_enchased"))->query("name")+"��\n");

	if (me->is_busy())
		return notify_fail("��æ����������������������ɣ�\n");

	if (me->is_fighting())
		return notify_fail("���������ڴ�ܣ�ûʱ������Щ���顣\n");

	if (me->query("max_jingli") < (100*num+300))
		return notify_fail("�����ڵľ�����Ϊ���ޣ��޷�ʩչ��˼���ķ�����\n");

	if (me->query("jingli") < (200*num+300))
		return notify_fail("�����ھ������ã��޷�ʩչ������\n");

	//message_vision(HIM "$N" HIM "��һЩ"+obj->query("name")+"����һ��Ĭ����ͨʹ���Ǳ仯��"NOR"\n", me);
	//me->start_busy(1);

	me->add("jingli", -200*num);
	me->add("max_jingli", -100*num);
	target = new(obj->query("can_be_enchased"));
	target->set_amount(num);
	obj->add_amount(-num*need);
	target->move(me);
	message_vision(HIW "������â�������ƺ������˲�ͬѰ�������顣"NOR"\n", me);   
	write("��ϲ��������"+num+"��"+target->query("name")+"��\n");

	return 1;
}

int help(object me)
{
write(@HELP
ָ���ʽ : combinue

���ָ��������㽫ĳЩ������Ʒ�ϲ���һ���µ���Ʒ����Щ���ܺ�
�������Ҫ����ȥ�����ˡ�ÿ�κϲ�������ʧһЩ���������ޡ����
Ҫ�ϲ��ļ�����Ʒ������ͬ������Ҫָ�����ǵ���ţ�������������
ʯ��Ƭ�����Ҫ��һ������Ҫ���룺

HELP
    );
    return 1;
}
