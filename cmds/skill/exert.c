// exert.c

#include <skill.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string str,ski,force;
	int result;
	
	seteuid(getuid());

	if (! arg)
		return notify_fail("��Ҫ���ڹ����ķ���ʲô��\n");

	if(sscanf(arg,"%s.%s",ski,arg)!=2)
	{
		str = "�ڹ�";
		ski = "force";
	}
	else str = "�ķ�";

	if (me->is_busy())
		return notify_fail("( ����һ��������û����ɣ�����ʩ��"+str+"��)\n");

	if (stringp(force = me->query_skill_mapped(ski)))
	{
		notify_fail("���޷�˳������ת��Ϣ��\n");
		if (SKILL_D(force)->do_effect(me))
		{
			write(query_notify_fail());
			return 1;
		}

		notify_fail("����CD�л�����ѧ��"+str+"��û�����ֹ��ܡ�\n");
		if (SKILL_D(force)->exert_function(me, arg))
		{
			if (random(120) < (int)me->query_skill(ski))
				me->improve_skill(force, 1, 1);
			return 1;
		} else if (SKILL_D(ski)->exert_function(me, arg))
		{
			if (random(120) < (int)me->query_skill(ski, 1))
				me->improve_skill(ski, 1, 1);
			return 1;
		}

		return 0;
	}

	return notify_fail("�������ü���ʹ�õ�һ��"+str+"��\n");
}

int help (object me)
{
	write(@HELP
ָ���ʽ��exert|yun <��������> [<ʩ�ö���>]

����������һЩ���칦�ܣ������Ҫָ��<��������>��<ʩ�ö���>����п��ޡ�
����ʹ��ĳһ���ڹ������칦��֮ǰ����������� enable ָ����ָ����Ҫʹ��
���ڹ���

��ο� help force �ɵ�֪һЩ�󲿷��ڹ����еĹ��ܣ����������õ��ڹ�����
��û�иù��ܣ���һ�Ի�ο�����˵����֪��

ע�������ı��Լ����ڹ�����ԭ�����������������ֱ��ת����ȥ������
    �ӣ���ʼ��

HELP );
	return 1;
}

