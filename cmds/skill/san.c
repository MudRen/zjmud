// ʥ��

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object item;

	if (! arg) return notify_fail("��Ҫʥ��ʲô��Ʒ��\n");

	//if (!wizardp(me)) return notify_fail("���ܸ��²����У��Ժ󿪷ţ�\n");

	if (! objectp(item = present(arg, me)))
		return notify_fail("������û��������Ʒ��\n");

	notify_fail(item->name() + "û�а취��ʥ����\n");

	// ʥ����Ʒ
	return item->do_san(me);
}

int help(object me)
{
write(@HELP
ָ���ʽ : san <��Ʒ����>
 
���ָ���������ʥ��ĳ����Ʒ����Ȼ�������Ʒ���ܹ�ʥ���ſ��ԣ�
��������Ҫ���㹻������������൱��ľ�����ʥ���Ժ������ʧһ
Щ�����;��������ޡ�

ֵ��ע����ǣ�ʥ��ʱ����������ˮƽû�г�ֶ�������Ŀǰ�ļ�
�ޣ���ʥ��������һ����Σ�գ��п��ܵ�����Ļ����ڹ��ܵ����ˡ�
�����ʥ��ǰ��֤�Լ��������ӽ�ƿ��ֵ�ǿɿ���������
HELP
    );
    return 1;
}
