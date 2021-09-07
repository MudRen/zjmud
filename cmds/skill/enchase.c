// enchase.c

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	string msg, item, tessera;
	object *baoshi,obj, dest;
	int i;

	if (! arg)
		return notify_fail("��Ҫ��ʲô��������Ƕ��Ʒ��\n");

	if (me->is_busy())
		return notify_fail("��æ����������������������ɣ�\n");

	if (me->is_fighting())
		return notify_fail("���������ڴ�ܣ�ûʱ������Щ���顣\n");

	if (sscanf(arg, "%s with %s", item, tessera) != 2)
	{
		baoshi = filter_array(all_inventory(me),(:$1->query("can_be_enchased"):));
		if(sizeof(baoshi))
		{
			msg = ZJOBLONG"��ѡ����Ҫ��Ƕ�ı�ʯ(��Ƕ��ʯ��Ҫ�����뱦ʯ������Ӧ�Ľ��)��\n"ZJOBACTS2+ZJMENUF(3,3,10,30);
			for(i=0;i<sizeof(baoshi);i++)
			{
				msg += baoshi[i]->query("name")+"("+baoshi[i]->query("magic/power")+"):enchase "+arg+" with "+file_name(baoshi[i]);
				if(i<(sizeof(baoshi)-1)) msg += ZJSEP;
			}
		}
		else
		{
			msg = ZJOBLONG"����������û�б�ʯ�����ܽ�����Ƕ��";
		}
		tell_object(me,msg+"\n");
		return 1;
	}

	if (! objectp(obj = present(tessera, me)))
		return notify_fail("������û��������������������Ƕ��\n");

	if (! objectp(dest = present(item, me)))
		return notify_fail("������û���������ߡ�\n");

	notify_fail("���޷���" + obj->name() + "��Ƕ��" + dest->name() + "�ϡ�\n");
	return dest->do_enchase(me, obj);
}

int help(object me)
{
write(@HELP
ָ���ʽ : enchase <����> with <������Ʒ>

���ָ��������㽫ĳ��������Ʒ��Ƕ������һ�ֵ����ϣ�ʹ�õ���
���������������
HELP
    );
    return 1;
}
