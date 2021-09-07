// register.c
// Created by Xiang@XKX
// Updated by doing

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

private int register_user(object me, string name, string email)
{
	object ob, body;

      	if (objectp(body = find_player(name)))
	{
		log_file("static/register",
			 sprintf("%s %s change %s email from %s to %s.\n",
				 log_time(), log_id(me), name,
				 body->query("email"), email));

		body->set("registered", 1);
		body->set("email", email);
		body->save();
		return 1;
	}

	ob = new(LOGIN_OB);
	ob->set("id", name);
	body = LOGIN_D->make_body(ob);
	destruct(ob);
	if (! body)
		destruct(ob);
	else
	if (! body->restore())
	{
		destruct(body);
	} else
	{
		log_file("static/register",
			 sprintf("%s %s change %s email from %s to %s.\n",
				 log_time(), log_id(me), name,
				 body->query("email"), email));

		body->set("registered", 1);
		body->set("email", email);
		body->save();
		destruct(body);
		return 1;
	}

	return 0;
}

int main(object me, string arg)
{
	string id, email;

	if (! SECURITY_D->valid_grant(me, "(arch)"))
		return 0;

	if (! arg || sscanf(arg, "%s %s", id, email) != 2)
		return notify_fail("ָ���ʽ��register <id> <email>\n");

	switch (register_user(me, id, email))
	{
	case 0:  return notify_fail("�Ǽ�ʧ�ܡ�\n"); break;
	default: return notify_fail("�û�(" + id + ")�Ѿ��ɹ��ر����Ǽ��ˡ�\n"); break;
	}
}

int help(object me)
{
	write(@HELP
ָ���ʽ��register <id> <email>

���ָ����Ը���û�еǼǹ����û����еǼǣ����߸��Ѿ��Ǽǵ���
���趨�µĵǼ����䡣
HELP );
	return 1;
}
