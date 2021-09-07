// pun.c

inherit F_CLEAN_UP;

private void cut_exp(object me, object ob, int scale);

int help(object me);

int main(object me, string arg)
{
	string target;
	object ob;
	string msg;
	function f;
	string user, flogin, fuser;

	if (! SECURITY_D->valid_grant(me, "(arch)"))
		return 0;

	seteuid(getuid(me));

	if (! arg) return notify_fail("ָ���ʽ : pun <���ID> <����>\n" );

	if (sscanf(arg, "%s %s", target, arg) != 2)
		return help(me);

	ob = UPDATE_D->global_find_player(target);
	if (! objectp(ob))
		return notify_fail("û�������ҡ�\n");

	switch (arg)
	{
	case "exp-10":
		f = (: cut_exp, me, ob, 10 :);
		break;

	case "exp-20":
		f = (: cut_exp, me, ob, 20 :);
		break;

	case "exp-30":
		f = (: cut_exp, me, ob, 30 :);
		break;

	case "exp-40":
		f = (: cut_exp, me, ob, 40 :);
		break;

	case "exp-50":
		f = (: cut_exp, me, ob, 50 :);
		break;

	case "exp-60":
		f = (: cut_exp, me, ob, 60 :);
		break;

	default:
		write("û���������취��\n");
		UPDATE_D->global_destruct_player(ob, 1);
		return 1;
	}

	user = getuid(ob);
	flogin = "login/" + user[0..0] + "/" + user + __SAVE_EXTENSION__;
	fuser  = "user/"  + user[0..0] + "/" + user + __SAVE_EXTENSION__;

	if (file_size(TEMP_DIR + flogin) >= 0 ||
	    file_size(TEMP_DIR + fuser) >= 0)
	{
		msg = "�����ݴ���(/temp/)�����Ѿ���������"
		      "�����ݣ���˱��β����ݴ档\n";
	} else
	{
		// move current user's data to /temp/
		assure_file(TEMP_DIR + flogin);
		assure_file(TEMP_DIR + fuser);
		cp(DATA_DIR + flogin, TEMP_DIR + flogin);
		cp(DATA_DIR + fuser,  TEMP_DIR + fuser);
		msg = "��� " + user + " Ŀǰ��������ʱ����"
		      "���ݴ���(/temp/)�¡�\n";
	}
	write(msg);

	evaluate(f);
	UPDATE_D->global_destruct_player(ob, 1);
	return 1;
}

private void cut_exp(object me, object ob, int scale)
{
	ob->set("combat_exp",
		ob->query("combat_exp") / 100 * (100 - scale));
	UPDATE_D->check_user(ob);
	ob->save();
	write(sprintf("��۳���%s�� %d%% ս�����顣\n",
		      ob->name(1), scale));
	tell_object(ob, sprintf("%s�۳����� %d%% ս�����顣\n",
				me->name(1), scale));
}

int help(object me)
{
	write(@HELP
ָ���ʽ : pun <���ID> <����>

�����ʹ������������ҵ����������������������ǰ��շ���
ָ���İ취���еġ�Ϊ�˷�ֹ�����������ǰϵͳ���Զ�����
��ҵĵ����������ݴ��������������Դ�����ָ����������
��Ҫ����ݴ�����

���������exp-10
	  exp-20
	  exp-30
	  exp-40
	  exp-50
	  exp-60

�ο����ϣ� restore, clear, cleartemp
HELP );
	return 1;
}

