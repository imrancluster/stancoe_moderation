<div class="content-for-creators">
    <h1>Content for manager</h1>
    <table class="content-manager">
        <thead>
        <tr>
            <th>NID</th>
            <th>Type</th>
            <th>Author</th>
            <th>Status</th>
            <th>Created</th>
            <th>Updated</th>
            <th>Action</th>
        </tr>
        </thead>
        <tbody>
        <?php foreach($data as $content): ?>
            <tr>
                <td><?php print $content['nid']; ?></td>
                <td><?php print $content['type']; ?></td>
                <td><?php print $content['uid']; ?></td>
                <td><?php print ($content['status'] == 1) ? 'published' : 'not published	'; ?></td>
                <td><?php print date('d/m/Y', $content['created']); ?></td>
                <td><?php print date('d/m/Y', $content['changed']); ?></td>
                <td><a href="/node/<?php print $content['nid']; ?>/edit">Edit</a></td>
            </tr>
        <?php endforeach; ?>
        </tbody>
    </table>
</div>