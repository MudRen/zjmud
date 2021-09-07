// clear.c

inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
	string target;
	object obj;
	object *obs;
	string ob_name;
	int remove_flag;

	if (! SECURITY_D->valid_grant(me, "(admin)"))
		return 0;

	seteuid(getuid(me));

	if (! arg) return notify_fail("ָ���ʽ : clear [-u] <���֮��"
				      "�ƻ���> | <���ID> <����>\n" );

	if (sscanf(arg, "-u %s", arg) == 1)
	{
		if (sscanf(arg, "%s %s", target, arg) != 2)
		{
			write("�����ָ������û���ʲô���ݡ�\n");
			return 1;
		}

		// clear the user data
		write ("����û�(" + target + ")�����ݣ�" +
		       UPDATE_D->clear_user_data(target, arg));
		return 1;
	}

	if (arg == "-u")
	{
		help(me);
		return 1;
	}

	// check the remove flag
	remove_flag = sscanf(arg, "-remove %s", arg);
	
	target = arg;
	obj = find_object(target);
	if ((! obj  || userp(obj)) && file_size(target + ".c") >0 )
		catch(obj = load_object(target));
	if (! obj || userp(obj)) obj = present(target, me);
	if (! obj || userp(obj)) obj = present(target, environment(me));
	if (! obj || userp(obj)) obj = find_object(resolve_path(me->query("cwd"), target));
	if (! obj || userp(obj)) catch(obj = load_object(resolve_path(me->query("cwd"), target)));
	if (obj && ! userp(obj))
	{
		message_vision(sprintf("$N�����<%O>��ͬ���̼�¼һ��"
				       "���׵Ĵݻ��ˡ�\n", obj), me);
		if (! clonep(obj))
		{
			obs = filter_array(all_inventory(obj), (: userp :));
			obs->move(VOID_OB, 1);
		} else
			obs = 0;

		target = base_name(obj);

		if (! DBASE_D->clear_object(obj))
			write ("��û���ܹ��ɹ��Ĵݻ�����ͼ�¼��\n");
		else
		{
			if (remove_flag)
			{
				seteuid(getuid());
				if (rm(target + ".c") == 1)
					write("�ļ� " + target + ".c �Ѿ��ɹ�ɾ����\n");
				else
					write("ɾ���ļ� " + target + ".c ʧ�ܡ�\n");
			} else
			if (arrayp(obs) && sizeof(obs))
				obs->move(target, 1);
			write("Ok.\n");
		}
	} else
	{
		write("����ͼ�����ݿ��������Ŀ(" + target + ")�ļ�¼��\n");
		if (! DBASE_D->clear_object(target))
			write ("��û���ܹ��ɹ��������¼��\n");
		else
			write("Ok.\n");
	}

	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : clear -u <���ID> <����>
		 [-remove] <���֮���ƻ���>

���ô�һָ��ɽ�һ�����(object)��ͬ���Ĵ��̼�¼һ�������ע
�⣺����Ĵ��̼�¼ָ�������ݱ����� DBASE_D �е���Щ���� ��
����¼�Ǳ���ɵ������ļ��������ǵĴ��̼�¼�����ܵ��κ�Ӱ�죬
����������ṩ����ʦ���ܵ����˵Ķ�����������޸�ʱʹ�õġ�

���ʹ�ò��� -u�����ʾ��Ҫ���һ����Ҷ� MUD �еĶ������ݣ�
����˵ס������Ϣ�Ϳ���ͨ�����������������ָ������ҵ�ס����
�١�

���������all      ��������
	  balance  ���
	  board    ���԰�
	  couple   ����
	  item     ����
	  name     ����
	  room     ����
	  brothers ����
	  league   ����
	  title    �ƺ�

���ʹ���� -remove ������ ��ʾ�������Ĵ��̼�¼�Ժ�ɾ�����
�ļ������������Ҫ����ʹ�á�

�ο����ϣ� dest��query
HELP );
	return 1;
}
