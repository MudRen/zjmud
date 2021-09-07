// info.c

inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
	object obj;
	string str;
	int ttl;
	string ext;

	if (! SECURITY_D->valid_grant(me, "(wizard)"))
		return 0;

	if (! arg) return help(me);

	seteuid(geteuid(me));

	if (arg == "me") obj = me;
	else if (arg == "my link") obj = me->query_temp("link_ob");
	else
	{
		obj = present(arg, me);
		if (! obj || ! me->visible(obj)) obj = present(arg, environment(me));
		if (! obj) obj = find_object(resolve_path(me->query("cwd"), arg));
		if (! obj || ! me->visible(obj)) obj = find_player(arg);
		if (! obj || ! me->visible(obj)) obj = find_living(arg);
		if (! obj) return notify_fail("û���������....��\n");
	}

	write(sprintf("��� [%O]\n-----------------------------------------------------\n", obj));
	write("������\t\t" + base_name(obj) + ".c\n");
	write("����\t\t" + domain_file(base_name(obj)) + "\n");
	write("���ߣ�\t\t" + author_file(base_name(obj)) + "\n");
	write("Ȩ�ޣ�\t\tuid = " + getuid(obj) + ", euid = " + geteuid(obj) + "\n");
	write("�ȼ���\t\t" + wizhood(obj) + "\n");
	write("ʹ�ü����壺\t" + memory_info(obj) + "\n");
	str = "";
	if (living(obj)) 	str += "���� ";
	if (userp(obj))		str += "ʹ���� ";
	if (interactive(obj))	str += "���� ";
	if (wizardp(obj))	str += "��ʦ ";
	if (clonep(obj)) 	str += "���� ";
	if (virtualp(obj)) 	str += "���� ";
	if (obj->query("env/invisible")) str += "���� ";
	if (query_heart_beat(obj)) str += "����:" + query_heart_beat(obj) + " ";
	write("���ԣ�\t\t" + str + "\n");

	if ((ttl = obj->query_time_to_leave()) > 0)
		write("���գ�\t\t" + appromix_time(ttl) + "\n");

	write("���Ƹ�����\t" + sizeof(children(base_name(obj)+".c")) + "\n");
	write("�ο����᣺\t" + refs(obj) + "\n");
	if (obj->is_telneting())
		write("Զ�̵�½��\t" + obj->query_dest_addr() + "\n");

	if (stringp(ext = obj->query_info()))
		write(ext);

	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : info <���֮���ƻ���>

���ô�һָ��ɵ�֪һЩ�йظ��������Ѷ��
HELP );
	return 1;
}
